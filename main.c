#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <dirent.h>

void traverse_directory(const char *path, int *counter);

const unsigned char DIRECTORY_TYPE = 4;
const unsigned char FILE_TYPE = 8;


int main(){

	size_t i;
	json_t *json;
	json_error_t error;

	json = json_load_file("test.json", 0, &error);
	printf("test\n");
	
	for(i = 0; i < json_array_size(json); i++)
	{
		json_t *data;
		json_t *widget, *debug_val;
		const char *buffer;
	
		
		printf("going into json_array: %d\n", (int)i);
		data = json_array_get(json, i);

		widget = json_object_get(data, "widget");
		if(!json_is_object(widget))
		{
			printf("widget is not an object\n");
		}
		
		debug_val = json_object_get(widget, "debug");
		
		buffer = json_string_value(debug_val);
		
		printf("Debug Value: %s", buffer);
		
	
	}

	int counter = 0;
	
	traverse_directory("/home/kwonga/Documents/json/test/tmp_data/", &counter);
	



	return 0;
}

void traverse_directory(const char *path, int *counter){
	DIR *directory;
	struct dirent *direntry;
	char filename[512];
	
	directory = opendir(path);
	
	if(directory){
		while((direntry=readdir(directory)) != NULL){
			if(direntry->d_type == DIRECTORY_TYPE){
				if(sizeof(filename) < sizeof(path) + sizeof(direntry->d_name) + 2){
					fprintf(stderr, "Directory path is too long: %s\n", path);
				} else{
					if(strcmp(direntry->d_name, ".") != 0 && strcmp(direntry->d_name, "..") != 0){
						strcpy(filename, path);
						strcat(filename, "/");
						strcat(filename, direntry->d_name);
						printf("Going into directory with name: %s, type: %u\n", direntry->d_name, direntry->d_type);
						printf("Combined directory name: %s\n\n", filename);
						traverse_directory(filename, counter);
					}
				}
			} else if(direntry->d_type == FILE_TYPE){
				printf("counter value: %d\n", *counter);
				*counter = *counter + 1;
				printf("File found: %s, type: %u\n", direntry->d_name, direntry->d_type);
			}
		}
	}
	closedir(directory);
}