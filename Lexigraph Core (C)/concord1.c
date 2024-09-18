#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int compString (char* str, char (arrstr)[1024][1024], int len) {
    int i=0;
    for(i = 0; i < len; i++) {
        if(!strncmp(arrstr[i], str, strlen(str))) {
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
        fprintf(stderr, "Unable to open %s\n", argv[1]);
        exit(1);
    }
    else {
        char stringfunc[1024];
        char stringmain[1024];
        char stringtemp[1024];
        char stringtempt[200][1024];
        bool foundduplicates = false;

        char stringbeg[] = "\'\'\'\'";
        char stringend[] = "\"\"\"\"";
        int i=0;
        char string1[200][1024];
        char avoidtype[200][1024];
        char string2[200][1024];
        char fleshtype[200][1024];
        char unorgUncapFlesh[200][1024];
        char temp[200][1024];
        // char organized[1024][1024];
        char capStocked[200][1024];
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
        
        int currVoidType=0;
        for (i=0; i<iter1; i++) {
            strncpy(avoidtype[i],string1[i],strlen(string1[i]));
            // fprintf(stdout,"avoidtype[%d]:\t%s\n",i,avoidtype[i]);
            ++currVoidType;
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
                // fprintf(stdout,"token <first> is: %s\n",token);
                strncpy(capStocked[helpermain++],token,strlen(token));
            } 

            while (token!=NULL) {
                token=strtok(NULL, " ");
                if ((token!=NULL)&&(compString(token,avoidtype,iter1)==1)) {
                    // fprintf(stdout,"token <second>: %s\n",token);
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

        i=0;
        while (i<helpermain) {
            int l=0;
            while ((l<helpermain)) {
                strncpy(stringfunc,string2[i],1024);
                if ((i!=l)&&(!strncmp(string2[i],string2[l],1024))) {
                    // fprintf(stdout,">>>%d[[%s]]/%d[[%s]] has match.\n",i,string2[i],l,string2[l]);
                    foundduplicates=true;
                }
                l++;
            }
            i++;
        }

        i=0;
        while (i<currVoidType) {
            int j=0;
            while (j<helpermain) {
                if (!strcmp(avoidtype[i],string2[j])) {
                    strcpy(string2[j],strlok);
                    // fprintf(stdout,"a{%s}x{%s}c\n",avoidtype[i],string2[j]);
                }
                ++j;
            }
            ++i;
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
        // // // // // // // // // // // // //  // // // // // // // // // // // // // // // // //
        // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
        
        // int testnum = 15;
        int gotmatches=0;
        if (foundduplicates)    {
            for (i=0; i<helpermain  ; i++) {
                strncpy(stringtemp,string2[i],strlen(string2[i]));
                strcat(stringtemp," ");
                if (strncmp(string2[i],strlok,31)==0) {continue;}
                int j=0;
                for (j=0; j<helpermain; j++) { 
                    if (strncmp(string1[j],strlok,31)==0) {continue;}
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
                                }                                                                                                    // string 2 i because this is the order we want
                        // fprintf(stdout,"<<<<<(foundrec)[%s]-->%s>>>>>\n",rect,string2[i]);
                                // fprintf(stdout,"\t\t>>>>crrstrmain[%s]\n",stringmain);
                        
                        
                        strncpy(stringtempt[j],stringmain,strlen(stringmain));
                        if ((j!=0)&&(!strncmp(stringtempt[j-1],stringtempt[j],1024))) {continue;}
                        fprintf(stdout,"%s\n",stringmain); // MAINFUNCTION
                        
                        strncpy(string2[i],strlok,31);
                        strncpy(string1[j],strlok,31);
                        ++gotmatches;
                        continue;
                    }
                    rect = strtok(NULL, " ");
                    
                    while ((rect!=NULL)&&(countOfString1!=0)) {
                    // fprintf(stdout,"\ntest0%d\t\t\trect is on \"%s\" string\nstring2i is on \t\t[%s] string \n\n",testnum,rect,string2[i]);//EBHVEBVHBVHJBVJHEDBVJHF
                        if (!strncmp(rect,string2[i],1024)) {   
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
                                }                                                                                                                                  // string 2 i because this is the order we want
                        // fprintf(stdout,"<<<<<(foundrec)[%s]-->%s>>>>>\n",rect,string2[i]);
                        
                        strncpy(stringtempt[j],stringmain,strlen(stringmain));
                        if ((j!=0)&&(!strncmp(stringtempt[j-1],stringtempt[j],1024))) {break;}
                        
                        fprintf(stdout,"%s\n",stringmain);
                        strncpy(string2[i],strlok,31);
                        strncpy(string1[j],strlok,31);
                        ++gotmatches;
                        }
                        --countOfString1;
                        rect = strtok(NULL, " ");
                    }
                }
            }
        } else {
            for (i=0; i<helpermain  ; i++) {
                strncpy(stringtemp,string2[i],strlen(string2[i]));
                strcat(stringtemp," ");
                if (strncmp(string2[i],strlok,31)==0) {continue;}
                int j=0;
                for (j=0; j<helpermain; j++) { 
                    if (strncmp(string1[j],strlok,31)==0) {continue;}
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
                        strncpy(string1[j],strlok,31);
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
                        strncpy(string1[j],strlok,31);
                        ++gotmatches;
                        }
                        --countOfString1;
                        rect = strtok(NULL, " ");
                    }
                }
            }
        }
        // // // // // // // // // // // // //  // // // // // // // // // // // // // // // // //
        // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

        // fprintf(stdout,"\n\ngotmatches total:%d\n",gotmatches);

        // fprintf(stdout,"\nSet of words revisited:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",string2[i]);
        // }
        // fprintf(stdout,"\nSet of strings revisited:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",string1[i]);
        // }
        // fprintf(stdout,"\nSet of stringtempt visited:\n");
        // for (int i=0; i<helpermain; i++) {
        //     fprintf(stdout,"{%s}\n",stringtempt[i]);
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