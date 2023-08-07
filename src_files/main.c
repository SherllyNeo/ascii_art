#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mjson.h"
#include <stddef.h>
#include "art.h"

#define SIZE 8000
#define ATTACHMENT_SIZE 8000
#define MAXOBJECTS  80000


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

int main(int argc, char *argv[])
{
    char json_list[ATTACHMENT_SIZE];
    char* attachment_buffer = art;
   // strncpy(json_list,argv[1],ATTACHMENT_SIZE);
    strncpy(json_list,attachment_buffer,art_len);



    /* Allocate space for object list */
    struct Art_Obj_list *obj_list = malloc(sizeof(struct Art_Obj_list));
    /* Call object list parsing function */
    int status = json_object_list_read(json_list, obj_list);

    if (status == 0) {
        int i;
        for (i = 0; i < obj_list->nobjects; i++) {
            printf("Object %d:\n", i);
            printf("  art: %s\n", obj_list->list[i].art);
           printf("  desc: %s\n", obj_list->list[i].desc);
            printf("  category: %s\n", obj_list->list[i].category);
            printf("  width: %d\n", obj_list->list[i].height);
            printf("  height : %d\n", obj_list->list[i].width);
        }
    } else {
        puts(json_error_string(status));
    }
    return EXIT_SUCCESS;
}
