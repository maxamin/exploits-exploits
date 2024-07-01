// Memory dump script for IDA Pro by jSacco
// How to use: Modify the start_address / end_address
// Run it from IDA: File -> Script File

static main()
{
auto fp, ea;
auto fname      = "dump_mem.bin";
auto start_address    = 0x400000; // From where?
auto end_address       = 0x40b200; // Until ?

auto file= fopen(fname, "wb");
for (ea=start_address; ea < end_address; ea++)
    fputc(Byte(ea),file);
//savefile(file, 0, address, size);
fclose(file);

Message("[?] Memory dump script by: jSacco - <jsacco@exploitpack.com>\n");
Message("[!] Saved as: %s\n", fname);
Message("[*] From: 0x%x\n", start_address);
Message("[*] End: 0x%x\n", end_address);
}