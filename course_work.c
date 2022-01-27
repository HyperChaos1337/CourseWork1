#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define step 5
 
//Создание структуры строки
 
struct Sentence{
    
    int size; // Размер буфера
    char *str;
    
};
 
//Создание структуры текста
 
struct Text{
    
    struct Sentence **sents;
    int count; // Количество предложений в тексте
    int size;
    
};
 
//Работа со строкой
struct Sentence* readSentence(){
    
    int size = step;
    char *buffer = malloc(sizeof(char)*step);
    char tmp;
    int i = 0;
    
    do{
        if(i >= size - 2){
            buffer = realloc(buffer, size + step); //Увеличение памяти в случае, если осталось 2 свободные ячейки
            size += step;
        }
        tmp = getchar();
        buffer[i] = tmp;
        i++;
    }while(tmp != '.' && tmp != '\n'); //Знаки препинания. На них заканчивается ввод предложения
    buffer[i] = '\0';
    
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence -> str = buffer;
    sentence -> size = size;
    
    return sentence;
    
}
 
//Проверка на повторное вхождение предложения. Возвращает соостветствующее логическое значение
int re_entry(struct Sentence **txt, struct Sentence *sent, int i){
    
    for(int j = 0; j < i; j++){
        int k = 0;
        for(int j1 = 0; j1 < strlen(sent -> str); j1++){
            if(tolower(txt[j]->str[j1]) == tolower(sent -> str[j1])){
                k++;
            }
        }
        if(k == strlen(sent -> str) && k == strlen(txt[j] -> str)){
            return 0;
        }
    }
    return 1;
}
 
//Работа с текстом
struct Text readText(){
    
    int size = step;
    struct Sentence** text = malloc(size*sizeof(struct Sentence*));
    int i = 0;
    struct Sentence* tmp;
    int lbcount = 0;
    
    do{
        tmp = readSentence();
        if (tmp -> str[0] == '\n'){
            lbcount++;
        }
        else {
            if (re_entry(text, tmp, i)){
                text[i] = tmp;
                i++;
            }
            lbcount = 0;
        }
    }while (lbcount < 2);
    
    struct Text txt;
    txt.size = size;
    txt.sents = text;
    txt.count = i;
    
    return txt;
    
}

void get_garbage(struct Sentence *sent){
    
    int len = strlen(sent -> str);
    int k = 0;
    for(int m = 0; m < len; m++){
        if (tolower(sent -> str[m]) == 'g' &&
        tolower(sent -> str[m+1]) == 'a' &&
        tolower(sent -> str[m+2]) == 'r' &&
        tolower(sent -> str[m+3]) == 'b' &&
        tolower(sent -> str[m+4]) == 'a' &&
        tolower(sent -> str[m+5]) == 'g' &&
        tolower(sent -> str[m+6]) == 'e') k++;
        }
        if (k == 0) printf("Clean!");
        else if (k >= 1 && k <= 5) printf("Must be washed");
        else if (k > 5) printf("It is a dump");
    
}

int compare(const void *a, const void *b){
    
    char vows[12] = ['A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'];
    char sent1;
    chat sent2;
    
    int start_with_vow1 = 0;
    int start_with_vow2 = 0;
    
    
}
 
int main(){
    
    puts("Введите текст. По окончании ввода нажмите клавишу Enter дважды: ");
    struct Text text = readText();
    puts("Выберите опцию:");
    puts("1. Вывести количество слов 'garbage' и результат");
    puts("2. Замена на входное предложение всех цифр в тексте");
    puts("3. Удалить предложения с 3-мя идущими подряд буквами в верхнем регистре");
    puts("4. Отсортировать по уменьшению количества слов начинающихся с гласной буквы\n");
    int a;
    scanf("%d", &a);
    for(int j = 0; text.count; j++){
        puts(text.sents[j] -> str);
    }
    
    switch(a){
        case 1:
        for(int j = 0; text.count; j++){
            get_garbage(text.sents[j]);
        }
        
    }
    
    return 0;
}
