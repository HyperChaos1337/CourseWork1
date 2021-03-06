#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define step 5
#define M 12
 
//Создание структуры строки
 
struct Sentence{
    
    int vow; //Количество гласных букв
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
            char *t = realloc(buffer, size + step); //Увеличение памяти в случае, если осталось 2 свободные ячейки
            if (!t){
                return NULL;
            }
            buffer = t;
            size += step;
        }
        tmp = getchar();
        if (i == 0 && tmp == ' ') continue;
        buffer[i] = tmp;
        i++;
    }while(tmp != '.' && tmp != '\n'); //Знаки препинания. На них заканчивается ввод предложения
    buffer[i] = tmp;
    buffer[i+1] = '\0';
    
    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence->str = buffer;
    sentence->size = size;
    sentence->m = i; 
    sentence->vow = 0;
    
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

void get_garbage(struct Text txt){ //Функция 1
    int p=0;
    for(int x = 0; x < txt.count; x++) {
            char *s = txt.sents[x]->str;
            int count = txt.sents[x]->m;
            int k = 0;
            if (p!=0) {
                for (int j = 0; j < count - 8; j++) {
                    if (tolower(s[j]) == ' ' &&
                        tolower(s[j + 1]) == 'g' &&
                        tolower(s[j + 2]) == 'a' &&
                        tolower(s[j + 3]) == 'r' &&
                        tolower(s[j + 4]) == 'b' &&
                        tolower(s[j + 5]) == 'a' &&
                        tolower(s[j + 6]) == 'g' &&
                        tolower(s[j + 7]) == 'e' &&
                        (tolower(s[j + 8]) == ' ' || (s[j + 8]) == '.' || (s[j + 8]) == ','))
                        k += 1;
                }
            }
            else {
                for (int j = 0; j < count - 7; j++) {
                    if (tolower(s[j]) == 'g' &&
                        tolower(s[j + 1]) == 'a' &&
                        tolower(s[j + 2]) == 'r' &&
                        tolower(s[j + 3]) == 'b' &&
                        tolower(s[j + 4]) == 'a' &&
                        tolower(s[j + 5]) == 'g' &&
                        tolower(s[j + 6]) == 'e' &&
                        (tolower(s[j + 7]) == ' ' || (s[j + 7]) == '.' || (s[j + 7]) == ','))
                        k += 1;
                }
            }
            if (k == 0) puts("Clear!");
            else if (k >= 1 && k <= 5) puts("Must be washed");
            else if (k > 5) puts("It is a dump");
            p=1;
    }
}

int sent_end(char sym) {
    if (sym == '\n')
        return 0;
    return 1;
}


char *new_sent_in(){
    
    int i = 0;
    int size = step * sizeof(char);
    char *sent = malloc(size);
    char sym;
    int flag = 0;
    do {
        sym = getchar();
        if (flag == 0 && sym >= 33) {
            flag = 1;
        }
        if (flag == 1) {
            sent[i] = sym;
            i++;
            size += step * sizeof(char);
            sent = realloc(sent, size);
        }
    } while (sent_end(sym));
    sent[i] = '\0';
    return sent;
    
}

void new_sent_out(){
    new_sent_in();
}

void replace_digits(struct Text txt){
    
    char *st = new_sent_in();
    
    for(int x = 0; x < txt.count; x++){
        
        char *s = txt.sents[x]->str;
        int y = 0;
        while(y < txt.sents[x]->m){
            if isdigit(s[y]){
                s = realloc(s, (txt.sents[x]->size+strlen(st))*sizeof(char));
                txt.sents[x]->str += strlen(st);
                memmove(txt.sents[x]->str+y+strlen(st), txt.sents[x]->str, (txt.sents[x]->m)-y);
                }
            else y++;
            }
        }
    
    for (int x = 0; x < txt.count; x++){
        struct Sentence *s = txt.sents[x];
        printf("%s\n", s->str);
    }
    
}

int cap_lets_in_a_row(struct Sentence *sent){ //Функция 3
    
    int len = strlen(sent->str);
    
    for (int x = 0; x < len-2; x++){
        if ((int)sent->str[x] >= 65 && (int)sent->str[x] <= 90){
            if ((int)sent->str[x+1] >= 65 && (int)sent->str[x+1] <= 90){
                if ((int)sent->str[x+2] >= 65 && (int)sent->str[x+2] <= 90) 
                return 1;
            }
        }
    }

    return 0;
    
}

void removeSent(struct Text *txt, int cap_lets){
    
    for(int x = cap_lets; txt->count; x++){
        memmove(txt->sents[x], txt->sents[x+1], sizeof(struct Sentence*));
    }
    
    free(txt->sents[txt->count]);
    
    txt->count--;
    txt->size--;
    
}

void delSent(struct Text txt){
    
}

int compare(const void * a, const void * b){ //Функция 4
    
    struct Sentence **sent1 = (struct Sentence**) a;
    struct Sentence **sent2 = (struct Sentence**) b;
    
    int start_with_vow1 = (*sent1)->vow;
    int start_with_vow2 = (*sent2)->vow;
    
    return start_with_vow2-start_with_vow1;
    
}

void sorting(struct Text txt){ //Функция 4(продолжение)

    char vows[M] = {'A', 'E', 'I', 'O', 'U', 'Y', 'a', 'e', 'i', 'o', 'u', 'y'};
    int x,k;
 
    for(x = 0; x < txt.count; x++){
        k=0;
        char *s = txt.sents[x]->str;
        int count = txt.sents[x]->m;
        for (int j=0;j<count;j++){
            if (s[j]==' ') k=0;
            else k++;
            if (k==1){
                for(int y = 0; y < M; y++){
                    if (s[j] == vows[y])
                        txt.sents[x]->vow++;
                }
            }
        }
    }
    qsort(txt.sents, txt.count, sizeof(struct Sentence*), compare);
    for (x = 0; x < txt.count; x++){
        struct Sentence *s = txt.sents[x];
        printf("%s\n", s->str);
    }
}

    
int main(){
    
    puts("Введите текст. По окончании ввода нажмите клавишу Enter дважды: ");
    struct Text text = readText();
    puts("Выберите опцию:");
    puts("1. Вывести количество слов 'garbage' и результат");
    puts("2. Замена на входное предложение всех цифр в тексте");
    puts("3. Удалить предложения с 3-мя идущими подряд буквами в верхнем регистре");
    puts("4. Отсортировать по уменьшению количества слов начинающихся с гласной буквы");
    puts("5. Выйти из программы\n");
    int a;
    scanf("%d", &a);
    
    switch(a){
        case(1):
            puts("Результат:");
            get_garbage(text);
            break;
        case(2):
            puts("Введите новую строку:");
            new_sent_in();
            new_sent_out();
            replace_digits(text);
            break;
        case(3):
            puts("Результат:");
            for(int x = 0; x < text.count; x++){
                if(cap_lets_in_a_row(text.sents[x])){
                    removeSent(&text, x);
                    x--;
                }
            }
            
            for(int x = 0; x < text.count; x++){
                puts(text.sents[x]->str);
            }
            break;
        case(4):
            puts("Результат:");
            sorting(text);
            break;
        case(5):
            puts("Пользователь запросил выход из программы");
            break;
        default:
            puts("Нет такой команды!");
            break;
    }
    
    for(int j = 0; text.count; j++){
        free(text.sents[j]);
    }
    
    free(text.sents);
    
    return 0;
}
