include_directories(include)
add_executable(libextract1
	src/main.c
	src/wav_file.c)
target_link_libraries(libextract1 
	creebies_core)