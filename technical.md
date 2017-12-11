# CREEBIES TECHNICAL DOCUMENTATION

# 1. CODES
- Struct SCreebiesFile: Represents a resources, wrapping around FILE*
- Pseudo code
	```c++
		struct SCreebiesFile {
			WORD destroy_func_offset;
			FILE* _file;
			WORD size;
			EFileType type;
		}
	```
- Enum ECreebiesFileType:
- Pseudo code
	```c++
		enum ECreebiesFileType {
			Unassigned = 0,
			Read = 1,
			Write = 2
		}
	```

- Enum ECreebiesLang:
- Pseudo code
	```c++
		enum ECreebiesLang {
			LangEnglish = 1,
			LangFrance = 2,
			LangGerman = 3,
			LangItalia = 4,
			LangSpain = 5
		}
	```

- Example in game code:
```c++
signed int __fastcall GetSplashScreenFileName(char* scr, int lan)
{
  signed int v2; 
  const char *v3; 

  v2 = 0;
  switch ( lan )
  {
    case 2:
      v2 = 1;
      if ( a1 )
      {
        v3 = "NOKIA_SPLASH_FR.BMP";
        goto LABEL_5;
      }
      break;
    case 3:
      v2 = 2;
      if ( a1 )
      {
        v3 = "NOKIA_SPLASH_GE.BMP";
        goto LABEL_5;
      }
      break;
    case 4:
      v2 = 3;
      if ( a1 )
      {
        v3 = "NOKIA_SPLASH_IT.BMP";
        goto LABEL_5;
      }
      break;
    case 5:
      v2 = 4;
      if ( a1 )
      {
        v3 = "NOKIA_SPLASH_SP.BMP";
        goto LABEL_5;
      }
      break;
    default:
      if ( a1 )
      {
        v3 = "NOKIA_SPLASH_EN.BMP";
LABEL_5:
        strcpy(a1, v3);
      }
      break;
  }
  return v2;
}```

# 2. Secert
- there is a trading creebies rom and a test room that has hidden in the game for
years =))
