#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int compString (char* str, char (arrstr)[1024][1024], int len) {
    for(int i = 0; i < len; i++) {
        if(strncmp(arrstr[i], str, strlen(str)) == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    FILE *out = stdout;

    //     for (int i=0; i<=argc;i++) {
    //         printf("%d, %s\n",argc,argv[i]);
    //     }
    //     printf("\n----------\n");

    if (in == NULL) {
        // fprintf(stderr, "Unable to open %s\n", argv[1]);
        exit(1);
    }
    else {
        char stringfunc[1024];
        char stringmain[1024];
        char stringtemp[1024];

        char stringbeg[] = "\'\'\'\'";
        char stringend[] = "\"\"\"\"";
        int i=0;
        char string1[1024][1024];
        char avoidtype[1024][1024];
        char string2[1024][1024];
        char fleshtype[1024][1024];
        char unorgUncapFlesh[1024][1024];
        char temp[1024][1024];
        // char organized[1024][1024];
        char capStocked[1024][1024];
        char* strlok = "<>><><>><><>";

        // // // // // // // // // // // // // // // // // // // // // // // //
        int iter1=i;
        while (fgets(stringmain,1024,stdin)!=NULL) {
            if ((strncmp(stringend,stringmain,4)==0)) {break;}
            else if ((strncmp(stringbeg,stringmain,4)==0)||(strchr(stringmain, '1')!=NULL)) {continue;}
            else if (((strncmp(stringend,stringmain,4)!=0))&&(strncmp(stringbeg,stringmain,4)!=0)){
                char* rect = strtok(stringmain, "\n");
                strncpy(string1[iter1++],rect,strlen(rect));
                // fprintf(stdout,"iter1:%d\t\tstring1:[%s]\tstringmain:[%s]\n",iter1,string1[iter1],stringmain);
            }
        }

        for (i=0; i<iter1; i++) {
            strncpy(avoidtype[i],string1[i],strlen(string1[i]));
            // fprintf(stdout,"avoidtype[%d]:\t%s\n",i,avoidtype[i]);
        }
        // // // // // // // // // // // // // // // // // // // // // // // // 

        // fprintf(stdout,"\n");

        // // // // // // // // // // // // // // // // // // // // // // // //
        i=0;
        int iter2=i;
        while (fgets(stringmain,1024,stdin)!=NULL) {   
            if (strncmp(stringmain,avoidtype[iter2],100)==0) {continue;}
            else {
                strncpy(string2[iter2],stringmain,strlen(stringmain));
            }
            iter2++;
        }

        for (i=0; i<iter2; i++) {
            strncpy(fleshtype[i],string2[i],1024);
            // fprintf(stdout,"fleshtype[%d]:\t%s",i,fleshtype[i]);
            // fprintf(stdout,"%ld",sizeof(fleshtype[i]));
        }
        // // // // // // // // // // // // // // // // // // // // // // // // 
        // fprintf(stdout,"\n");
        
        for (i=0; i<iter2; i++) {
            strncpy(temp[i],fleshtype[i],1024);
            // fprintf(stdout,"temp[%d]:\t%s",i,temp[i]);
        }

        i=0;
        int helpermain=0;
        for (i=0; i<iter2; i++) {
            int helperinside=0;
            char *token =strtok(temp[i], " ");
            if (compString(token,avoidtype,iter1)==1) {helperinside++;} 

            while (token!=NULL) {
                token=strtok(NULL, " ");
                if ((token!=NULL)&&(compString(token,avoidtype,iter1)==1)) {helperinside++;} 
            }

            while (helperinside!=0) {
                strncpy(unorgUncapFlesh[helpermain++],fleshtype[i],strlen(fleshtype[i]));
                --helperinside;
            }
        }

        for (i=0; i<iter2; i++) {
            strncpy(temp[i],fleshtype[i],1024);
        }
        // fprintf(stdout,"\n");
        
        helpermain=0;
        for (i=0; i<iter2; i++) {
            // int helperinside=0;
            char *token =strtok(temp[i], " ");
            if ((compString(token,avoidtype,iter1)==1)&&(compString(token,capStocked,helpermain)==1)) {
                fprintf(stdout,"token <first> is: %s\n",token);
                strncpy(capStocked[helpermain++],token,strlen(token));
            } 

            while (token!=NULL) {
                token=strtok(NULL, " ");
                if ((token!=NULL)&&(compString(token,avoidtype,iter1)==1)&&(compString(token,capStocked,helpermain)==1)) {
                    fprintf(stdout,"token <second>: %s\n",token);
                    strncpy(capStocked[helpermain++],token,strlen(token));
                }
            }

        }

        for (i=0; i < helpermain; i++){
            int j=0;
            for (j = i + 1; j < helpermain; j++){
                if (strcmp(capStocked[i],capStocked[j])>0){
                    strncpy(stringtemp,capStocked[i],sizeof(capStocked[i]));
                    strncpy(capStocked[i],capStocked[j],sizeof(capStocked[j]));
                    strncpy(capStocked[j],stringtemp,sizeof(stringtemp));
                }
            }
        }
        
        for (i=0; i<helpermain; i++) {
            char* stringtemp = capStocked[i];
            char* iter1 = strtok(stringtemp,"\n");
            char* iter2 = strtok(unorgUncapFlesh[i],"\n");
            if ((iter1!=NULL)&&(iter2!=NULL))    {            
            strncpy(string1[i],unorgUncapFlesh[i],1024);
            strncpy(string2[i],capStocked[i],1024);
            }
        }
        // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
        // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
        // fprintf(stdout,"\nSet of Strings:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",string1[i]);
        // }
        // fprintf(stdout,"\nSet of words:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",string2[i]);
        // }


        // fprintf(stdout,"\n--------------------/n--------------------\n");
        // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
        // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
        // int testnum = 13;
        int gotmatches=0;
        for (i=0; i<helpermain  ; i++) {
            strncpy(stringtemp,string2[i],strlen(string2[i]));
            strcat(stringtemp," ");
            if (strncmp(string2[i],strlok,31)==0) {continue;}
            int j=0;
            for (j=0; j<helpermain; j++) { 
                strncpy(stringfunc,string1[j],sizeof(string1[j]));
                strncpy(stringmain,string1[j],sizeof(string1[j]));
                strncat(stringfunc," ",2);
                int countOfString1 = strlen(string1[j]);
                // int countOfString2 = strlen(string2[i]);
                // fprintf(stdout,"i[] j[] string1{%s}[%d] iterating through string2{%s}[%d]\n",string1[j],countOfString1,string2[i],countOfString2);                                      // string 1 j because we're working on it
                char* rect = strtok(stringfunc," ");                                                                                                                         // stringmain will printout the lines, hopefully
                // fprintf(stdout,"\ntest0%d\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",testnum,rect,string2[i]);//EBHVEBVHBVHJBVJHEDBVJHF
                if ((rect!=NULL)&&(!strncmp(rect,string2[i],1024))) {   
                            {
                            int k=0;
                            int count=0;
                            int counttrack=count;
                            int softcount;
                            int countbegin=0;
                                // fprintf(stdout,"\n\n\n");
                                while (stringmain[k]!='\0') {
                                    if (rect[count]==string1[j][k]) {
                                        // fprintf(stdout,"1-->%c\t2-->%c\n",rect[count],stringmain[k]);
                                        count++;
                                        counttrack=count;
                                        softcount=k;
                                        // fprintf(stdout,"sftcnt:%d\n",softcount);
                                        if (count==(int)strlen(rect)) {break;}
                                    } else (count=0); 
                                k++;
                                }
                                // fprintf(stdout,"[%d]%s:count:%d\ncounttrack(last highest count):%d sizeof():%d softcount:%d\n",j,rect,count,counttrack,(int)strlen(rect),softcount);
                                if (counttrack==(int)strlen(rect)) {
                                    countbegin=softcount-counttrack+1; // 15 = 22 - 8 + 1
                                    // fprintf(stdout,"countbegin:%d\n",countbegin);
                                    while (countbegin<=softcount) {
                                        // fprintf(stdout,"k:[%d] countbegin:[%d] countend: [%d]\n",k,countbegin, countend);
                                        stringmain[countbegin]=toupper(stringmain[countbegin]);
                                        countbegin++;
                                    } 
                                }
                            }                                                                                                                 // string 2 i because this is the order we want
                    // fprintf(stdout,"<<<<<(foundrec)[%s]-->%s>>>>>\n",rect,string2[i]);
                    fprintf(stdout,"%s\n",stringmain); // MAINFUNCTION
                    strncpy(string2[i],strlok,31);
                    ++gotmatches;
                    continue;
                }
                rect = strtok(NULL, " ");
                
                while ((rect!=NULL)&&(countOfString1!=0)) {
                // fprintf(stdout,"\ntest0%d\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",testnum,rect,string2[i]);//EBHVEBVHBVHJBVJHEDBVJHF
                    if (!strncmp(rect,string2[i],1024)) {                                                                                                                                    // string 2 i because this is the order we want
                            {
                            int k=0;
                            int count=0;
                            int counttrack=count;
                            int softcount;
                            int countbegin=0;
                                // fprintf(stdout,"\n\n\n");
                                while (stringmain[k]!='\0') {
                                    if (rect[count]==string1[j][k]) {
                                        // fprintf(stdout,"1-->%c\t2-->%c\n",rect[count],stringmain[k]);
                                        count++;
                                        counttrack=count;
                                        softcount=k;
                                        // fprintf(stdout,"sftcnt:%d\n",softcount);
                                        if (count==(int)strlen(rect)) {break;}
                                    } else (count=0); 
                                k++;
                                }
                                // fprintf(stdout,"[%d]%s:count:%d\ncounttrack(last highest count):%d sizeof():%d softcount:%d\n",j,rect,count,counttrack,(int)strlen(rect),softcount);
                                if (counttrack==(int)strlen(rect)) {
                                    countbegin=softcount-counttrack+1; // 15 = 22 - 8 + 1
                                    // fprintf(stdout,"countbegin:%d\n",countbegin);
                                    while (countbegin<=softcount) {
                                        // fprintf(stdout,"k:[%d] countbegin:[%d] countend: [%d]\n",k,countbegin, countend);
                                        stringmain[countbegin]=toupper(stringmain[countbegin]);
                                        countbegin++;
                                    } 
                                }
                            }
                    // fprintf(stdout,"<<<<<(foundrec)[%s]-->%s>>>>>\n",rect,string2[i]);
                    fprintf(stdout,"%s\n",stringmain);
                    strncpy(string2[i],strlok,31);
                    ++gotmatches;
                    }
                    --countOfString1;
                    rect = strtok(NULL, " ");
                }
            }
        }

        // fprintf(stdout,"\n\ngotmatches total:%d\n",gotmatches);

        // fprintf(stdout,"\nSet of words revisited:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",string2[i]);
        // }
        // fprintf(stdout,"\nSet of strings revisited:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",string1[i]);
        // }
// TEST
        // i=0;
        // {        
        //     int j=2;
        //     fprintf(stdout,"->%d",helpermain);
        //     char *rect = strtok(string1[j], " ");
        //     fprintf(stdout,"\n<test>\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",rect,string2[i]); // DEBUG TOOL
        //     strncpy(stringmain, rect, strlen(rect)); // stringmain will printout the lines, hopefully
        //     if (!strncmp(rect, string2[i], 1024))
        //     { // string 2 i because this is the order we want
        //         fprintf(stdout,"([1]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<foundrec)[%s]-->%s>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",rect,string2[i]);
        //         strncpy(string2[i], "complete", 9);
        //     }
        //     rect = strtok(NULL, " ");
        //     fprintf(stdout,"\n<test>\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",rect,string2[i]); // DEBUG TOOL
        //     if ((rect!=NULL)&&(!strncmp(rect, string2[i], 1024)))
        //     { 
        //         fprintf(stdout,"([2]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<foundrec)[%s]-->%s>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",rect,string2[i]);
        //         strncpy(string2[i], "complete", 9);
        //     }
        //     rect = strtok(NULL, " ");
        //     fprintf(stdout,"\n<test>\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",rect,string2[i]); // DEBUG TOOL
        //     if ((rect!=NULL)&&(!strncmp(rect, string2[i], 1024)))
        //     { 
        //         fprintf(stdout,"([3]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<foundrec)[%s]-->%s>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",rect,string2[i]);
        //         strncpy(string2[i], "complete", 9);
        //     }
        //     rect = strtok(NULL, " ");
        //     fprintf(stdout,"\n<test>\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",rect,string2[i]); // DEBUG TOOL
        //     if ((rect!=NULL)&&(!strncmp(rect, string2[i], 1024)))
        //     { 
        //         fprintf(stdout,"([4]<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<foundrec)[%s]-->%s>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n",rect,string2[i]);
        //         strncpy(string2[i], "complete", 9);
        //     }
        //     i++;
        // }

        // TEST

        // fprintf(stdout,"\n\n\n\niter1:%d iter2:%d",iter1,iter2);
        fclose(in);
        // fprintf(stdout, "\n\n\nI have been here!\n");
        fclose(out);
        return 0;
    }
}