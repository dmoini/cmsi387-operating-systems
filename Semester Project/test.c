#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE * fp = popen("ps -ev", "r");
    char buf[1024];
    char *p = strtok(fp, " ");
    // printf("%s\n", p);
    char *rc = (char*)1;
    int cpuIndex = 10;
    while (rc) {
        rc = fgets(buf, 1024, fp);
        
        char *p = strtok(rc, " ");
        for (int i = 0; i < cpuIndex; i++) {
            p = strtok(NULL, " ");
        }

        printf("%s\n", p);

        // double pVal = (double)((int) p);
        // printf("%f\n", pVal);

        // if (pVal > 2) {
        //     printf("returned: \"%s\"\n", buf);
        // }
        
        // p = strtok(NULL, " ");
        // p = strtok(NULL, " ");
        // printf("%s\n", p);
    }
    return 0;
    
    // char buf[] ="abc/qwe/ccd";
    // int i = 0;
    // char *p = strtok (buf, "/");
    // printf("%s\n", p);
    // p = strtok (NULL, "/");
    // printf("%s\n", p);
    // char *array[3];

    // while (p != NULL)
    // {
    //     array[i++] = p;
    //     p = strtok (NULL, "/");
    // }

    // for (i = 0; i < 3; ++i) 
    //     printf("%s\n", array[i]);

    // return 0;
}

// char * get_field(char *buffer, int field) {
//     int white = 1; // simple state machine
//     char *p;
//     char *first = NULL;
//     for (p=buffer; *p; p++) {
//         if (white) {
//             if (*p > ' ') {
//                 white = 0;
//                 first = p;
//             }
//         } else {
//             if (*p <= ' ') {
//                 white = 1;
//                 field--;
//                 if (!field && first)
//                     return strndup(first, p-first);
//             }
//         }
//     }
//     return NULL;
// }

// int main() {
//     FILE * fp = popen("ps -ev", "r");
//     char buf[1024];
//     char *rc = (char*)1;
//     while (rc) {
//         rc = fgets(buf, 1024, fp);

//         char *cpu = get_field(buf, 11);
//         if (cpu) {
//             printf("  cpu: \"%s\"\n", cpu);
//             free(cpu);
//         }
//         char *command = get_field(buf, 13);
//         if (command) {
//             printf("  command: \"%s\"\n", command);
//             free(command);
//         }
//     }
//     return 0;
// }