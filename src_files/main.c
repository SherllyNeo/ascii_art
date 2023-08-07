#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mjson.h"
#include <stddef.h>
#include "art.h"

#define SIZE 8000
#define ATTACHMENT_SIZE 8000
#define MAXOBJECTS  80000
#define MAXCAT 200


/* Data object to model */
struct Art_Obj {
    char art[SIZE];
    char desc[SIZE];
   char category[SIZE];
    int width;
    int height;
};

/* List of objects */
struct Art_Obj_list {
    int nobjects;
    struct Art_Obj list[MAXOBJECTS];
};


int json_object_list_read(const char *buf, struct Art_Obj_list *obj_list) {

    /* Mapping of JSON attributes to Art_Obj's struct members */
    const struct json_attr_t json_attrs_subobject[] = {
        {"art", t_string, STRUCTOBJECT(struct Art_Obj, art),
                .len = sizeof(obj_list->list[0].art)},
        {"desc", t_string, STRUCTOBJECT(struct Art_Obj, desc),
                .len = sizeof(obj_list->list[0].desc)},
       {"category", t_string, STRUCTOBJECT(struct Art_Obj, category),
                .len = sizeof(obj_list->list[0].category)},
        {"width", t_integer, STRUCTOBJECT(struct Art_Obj, width)},
        {"height", t_integer, STRUCTOBJECT(struct Art_Obj, height)},
        {NULL},
    };

    /* Mapping of JSON attributes to Art_Obj_list's struct members */
    const struct json_attr_t json_attrs_objects[] = {
        {"class", t_check, .dflt.check = "OBJECTS"},
        {"ASCII_ART_OBJECTS", t_array, STRUCTARRAY(obj_list->list,
                json_attrs_subobject,
                &(obj_list->nobjects))},
        {NULL},
    };

    memset(obj_list, '\0', sizeof(*obj_list));
    return json_read_object(buf, json_attrs_objects, NULL);
}

bool check_if_category_is_in_list(char* category_list[MAXCAT],int size_of_object_list ,char* category) {
        bool flag = false;
        for (int i = 0; i < size_of_object_list; i++) {
            char current_cat[MAXCAT];
            strcpy(current_cat,category_list[i]);
            if (strcmp(current_cat,category) == 0) {
                flag = true;
            }
        }
        return flag;
    
}

void get_list_of_categories(struct Art_Obj_list *obj_list,char** category_list,int category_init_size) {
        int i;
        int category_list_size = category_init_size;
        for (i = 0; i < obj_list->nobjects; i++) {
            char current_category[MAXCAT];
            strcpy(current_category,obj_list->list[i].category);
            printf("\nchecking to see if we've seen %s before\n",current_category);
            if (check_if_category_is_in_list(category_list, category_list_size, current_category)) {
                printf("\nseen %s before\n",current_category);
                continue;
            }
            else {
                /* add new category */
               // strcpy(category_list[i],current_category);
                category_list_size++;
                printf("\nadded new\n");
            }
        }

        for (int j =0; j<category_list_size;j++) {
            printf("\n%d - %s\n",i,category_list[j]);
        }
}


int main(int argc, char *argv[])
{
    char json_list[ATTACHMENT_SIZE];
    char* attachment_buffer = art;
    strncpy(json_list,attachment_buffer,art_len);



    /* Allocate space for object list */
    struct Art_Obj_list *obj_list = malloc(sizeof(struct Art_Obj_list));
    /* Call object list parsing function */
    int i;
    int status = json_object_list_read(json_list, obj_list);

    if (status == 0) {
        printf("\nRead json succesfully\n");
    } else {
        puts(json_error_string(status));
    }
    char* category_list[MAXCAT];
    get_list_of_categories(obj_list,category_list,0);
    return EXIT_SUCCESS;
}
