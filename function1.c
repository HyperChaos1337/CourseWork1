void get_garbage(struct Sentence *sent){
    
    int len = strlen(sent -> str);
    int m;
    
    do{
        sent -> str[m] = tolower(sent -> str[m]);
    }while (m < len);
    
    int k = 0;
    for(int m = 0; m < strlen(sent -> str); m++){
        if(sent -> str[m] == 'g' &&
        sent -> str[m+1] == 'a' &&
        sent -> str[m+2] == 'r' &&
        sent -> str[m+3] == 'b' &&
        sent -> str[m+4] == 'a' &&
        sent -> str[m+5] == 'g' &&
        sent -> str[m+6] == 'e') k += 1;
        }
        if (k == 0){
            puts("Clean!");
        }
        else if (k >= 1 && k <= 5){
            puts("Must be washed");
        }
        else if (k > 5){
            puts("It is a dump");
        }
    
}
