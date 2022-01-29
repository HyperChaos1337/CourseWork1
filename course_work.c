#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define step 5
#define M 12
 
//Создание структуры строки
 
struct Sentence{
    
    int m; //Количество символов
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
    sentence->str = buffer;
    sentence->size = size;
    sentence->m = i; 
    
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

void get_garbage(struct Text *txt){ //Функция 1
    
    for(int x = 0; x < txt->count; x++){
        char *s = txt->sents[x]->str;
        int len = strlen(txt->sents[x]->str);
        int k = 0;
        for(int j = 0; j < len-6; j++){
            if(tolower(s[j]) == 'g' &&
            tolower(s[j+1]) == 'a' &&
            tolower(s[j+2]) == 'r' &&
            tolower(s[j+3]) == 'b' &&
            tolower(s[j+4]) == 'a' &&
            tolower(s[j+5]) == 'g' &&
            tolower(s[j+6]) == 'e') k += 1;
        }
        if (k == 0) puts("Clear!");
        else if (k >= 1 && k <= 5) puts("Must be washed");
        else if (k > 5) puts("It is a dump");
    }
}

int cap_lets_in_a_row(struct Sentence *sent){ //Функция 3
    
    for(int x = 0; x < strlen(sent->str)-2; x++){
            if (sent->str[x] == toupper(sent->str[x]) &&
            sent->str[x+1] == toupper(sent->str[x+1]) &&
            sent->str[x+2] == toupper(sent->str[x+2])) return 1;
    }
    return 0;
}

void clear_cap_lets(struct Text *txt, int c){ //Функция 3(продолжение)
    for (int x = c; x < txt->count-1; x++){
        memmove(txt->sents[x], txt->sents[x+1], sizeof(struct Sentence*));
    }
    free(txt->sents[txt->count]);
    
    txt->count -= 1;
    txt->size -= 1; 
}

int compare(const void * a, const void * b){ //Функция 4
    
    char vows[M] = {'A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'};
    
    char **snt1 = (char**) a;
    char **snt2 = (char**) b;
    
    int start_with_vow1 = 0;
    int start_with_vow2 = 0;
    
    char * sent1 = *snt1;
    char * sent2 = *snt2;
    
    int k;
    
    for (k = 0; k < strlen(sent1); k++){
        for (int l = 0; l < M; l++){
            if(sent1[0] = vows[l]) start_with_vow1++;
        }
    }
    
    for (k = 0; k < strlen(sent2); k++){
        for (int l = 0; l < M; l++){
            if(sent2[0] = vows[l]) start_with_vow2++;
        }
    }
    
    if (start_with_vow1 > start_with_vow2) return 1;
    else if (start_with_vow1 == start_with_vow2) return 0;
    else if (start_with_vow1 < start_with_vow2) return -1;
    
}
 
void sorting(struct Text *txt){ //Функция 4(продолжение)
    
    char vows[M] = {'A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'};
    int x;
    
    for(x = 0; x < txt->count; x++){
        
        char *s = txt->sents[x]->str;
        int count = txt->sents[x]->m;
        int k = 0;
        for(int y = 0; y < M; y++){
            if (s[0] == vows[y]) k++;
        }
    qsort(txt->sents, txt->count, sizeof(struct Sentence*), compare);
    for(x = 0; x < txt->count; x++){
        struct Sentence *s = txt->sents[x];
        printf("%s\n", s->str);
    }
    
}

    
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
        case(1):
            get_garbage(&text);
            break;
        case(3):
            for(int j = 0; j < text.count; j++){
                if (cap_lets_in_a_row(text.sents[j])){
                    clear_cap_lets(&text, j);
                    j--;
                }
            }
            break;
        case(4):
            sorting(&text);
            break;
    }
    
    return 0;
}
