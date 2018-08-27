// tcc -lcjson -run test_json.c
#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main(void) 
{
	cJSON *body = cJSON_CreateObject();
    
	cJSON_AddItemToObject(body, "terminal_id", cJSON_CreateString("998877"));
	cJSON_AddItemToObject(body, "from_date", cJSON_CreateString("2017-05-15"));
	cJSON_AddItemToObject(body, "to_date", cJSON_CreateString("2017-05-19"));
    
	char* body_string = cJSON_PrintUnformatted(body);
    printf("%s\n", body_string);
    free(body_string);
    
    char* body_string_formatted = cJSON_Print(body);
    printf("%s\n", body_string_formatted);
    free(body_string_formatted);
    
	cJSON_Delete(body);

	return EXIT_SUCCESS;
}