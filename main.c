#include <stdlib.h>
#include <string.h>
#include <jansson.h>


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



	return 0;
}

