
[1m[37mTokens:
----------------[0m
[00] [31mOPEN[0m:   => (
[01] [32mCMD[0m:   => ls
[02] [36mARG[0m:   => -la
[03] [33mPIPE[0m:   => |
[04] [32mCMD[0m:   => grep
[05] [36mARG[0m:   => "txt"
[06] [35mOUT[0m:   => >
[07] [34mFILE[0m:   => text_files.list
[08] [33mAND[0m:   => &&
[09] [31mOPEN[0m:   => (
[10] [32mCMD[0m:   => cat
[11] [35mIN[0m:   => <
[12] [34mFILE[0m:   => Makefile
[13] [32mCMD[0m:   => -e
[14] [31mCLOSE[0m:   => )
[15] [31mCLOSE[0m:   => )
[16] [33mAND[0m:   => &&
[17] [32mCMD[0m:   => echo
[18] [36mARG[0m:   => "Text files found:"
[19] [33mAND[0m:   => &&
[20] [32mCMD[0m:   => cat
[21] [36mARG[0m:   => text_files.list
[22] [33mOR[0m:   => ||
[23] [31mOPEN[0m:   => (
[24] [32mCMD[0m:   => echo
[25] [36mARG[0m:   => "No text files found"
[26] [35mAPPEND[0m:   => >>
[27] [34mFILE[0m:   => error.log
[28] [33mAND[0m:   => &&
[29] [32mCMD[0m:   => exit
[30] [36mARG[0m:   => 1
[31] [31mCLOSE[0m:   => )
[32] [33mPIPE[0m:   => |
[33] [32mCMD[0m:   => wc
[34] [36mARG[0m:   => -l
[35] [35mIN[0m:   => <
[36] [34mFILE[0m:   => input.txt
[37] [35mAPPEND[0m:   => >>
[38] [34mFILE[0m:   => results.log
[39] [1m[37mEOF[0m:   => NULL
[1m[37m----------------
[0m