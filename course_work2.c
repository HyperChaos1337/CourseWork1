#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define step 5
#define M 12

struct Sentence{

    int vow;
    int m;
    int size;
    char *str;

};

struct Text{

    struct Sentence **sents;
    int count;
    int size;

};

struct Sentence* readSentence(){

    int size = step;
    char *buffer = malloc(sizeof(char)*step);
    char tmp;
    int i = 0;

    do{
        if(i >= size - 2){
            char *t = realloc(buffer, size + step);
            if (!t){
                return NULL;
            }
            size += step;
            buffer = t;
        }
        tmp = getchar();
        if (i == 0 && tmp == ' ') continue;
        buffer[i] = tmp;
        i++;
    }while(tmp != '.' && tmp != '\n');
    buffer[i] = '\0';

    struct Sentence *sentence = malloc(sizeof(struct Sentence));
    sentence->str = buffer;
    sentence->size = size;
    sentence->m = i;
    sentence->vow = 0;

    return sentence;

}

int re_entry(struct Sentence **sent1, struct Sentence *sent2, int i){

    for(int j = 0; j < i; j++){
        int k = 0;
        for(int l = 0; l < strlen(sent2 -> str); l++){
            if(tolower(sent1[j]->str[l]) == tolower(sent2 -> str[l])){
                k++;
            }
        }
        if(k == strlen(sent2 -> str) && k == strlen(sent1[j] -> str)){
            return 0;
        }
    }
    return 1;
}

struct Text readText(){

    int size = step;
    struct Sentence** text = malloc(size*sizeof(struct Sentence*));
    int i = 0;
    struct Sentence* tmp;
    int lbcount = 0;

    do{
        tmp = readSentence();
        if (i >= size - 2){
            struct Sentence **t = realloc(text, (size + step)*sizeof(struct Sentence*));
            if (!t){
                puts("Allocation error!");
            }
            text = t;
            size += step;
        }
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

void get_garbage(struct Text txt){
    int p = 0;
    for(int x = 0; x < txt.count; x++) {
        char *s = txt.sents[x]->str;
        int count = txt.sents[x]->m;
        int k = 0;
        if (p != 0) {
            for (int j = 0; j < count - 8; j++) {
                if (tolower(s[j]) == ' ' &&
                    tolower(s[j+1]) == 'g' &&
                    tolower(s[j+2]) == 'a' &&
                    tolower(s[j+3]) == 'r' &&
                    tolower(s[j+4]) == 'b' &&
                    tolower(s[j+5]) == 'a' &&
                    tolower(s[j+6]) == 'g' &&
                    tolower(s[j+7]) == 'e' &&
                    (tolower(s[j+8]) == ' ' || (s[j + 8]) == '.' || (s[j + 8]) == ','))
                    k += 1;
            }
        }
        else {
            for (int j = 0; j < count - 7; j++) {
                if (tolower(s[j]) == 'g' &&
                    tolower(s[j+1]) == 'a' &&
                    tolower(s[j+2]) == 'r' &&
                    tolower(s[j+3]) == 'b' &&
                    tolower(s[j+4]) == 'a' &&
                    tolower(s[j+5]) == 'g' &&
                    tolower(s[j+6]) == 'e' &&
                    (tolower(s[j+7]) == ' ' || (s[j + 7]) == '.' || (s[j + 7]) == ','))
                    k += 1;
            }
        }
        if (k == 0) puts("Clear!");
        else if (k >= 1 && k <= 5) puts("Must be washed");
        else if (k > 5) puts("It is a dump");
        p = 1;
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
    do {
        sym = getchar();
        sent[i] = sym;
        i++;
        size += step * sizeof(char);
        sent = realloc(sent, size);

    } while (sent_end(sym));
    sent[i] = '\0';
    return sent;

}

void new_sent_out(){
    new_sent_in();
}

void replace_digits(struct Text txt){

    new_sent_out();
    char *s_new = new_sent_in();

    for(int x = 0; x < txt.count+1; x++){
        puts("\n");
        char *s = txt.sents[x]->str;
        int count = txt.sents[x]->m;
        for(int y = 0; y < count; y++){
            if(!isdigit(s[y])) printf("%c", s[y]);
            else if(isdigit(s[y])){
                for(int z = 0; z < strlen(s_new); z++){
                    if (s_new[z] != '\n') printf("%c", s_new[z]);
                }
            }
        }
    }
}

int cap_lets_in_a_row(struct Sentence *sent){

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

void removal(struct Text *txt, int cap){

    free(txt->sents[cap]->str);

    for(int x = cap; x < txt->count-1; x++){
        memmove(txt->sents[x], txt->sents[x+1], sizeof(struct Sentence*));
    }
    free(txt->sents[txt->count]);

    txt->count--;
    txt->size--;

}

void delSent(struct Text *txt){

    int x;

    for(x = 0; x < txt->count; x++){
        if (cap_lets_in_a_row(txt->sents[x])){
            removal(txt, x);
            x--;
        }
    }

    for (x = 0; x < txt->count; x++){
        struct Sentence *s = txt->sents[x];
        printf("%s\n", s->str);
    }

}

int compare(const void * a, const void * b){

    struct Sentence **sent1 = (struct Sentence**) a;
    struct Sentence **sent2 = (struct Sentence**) b;

    int start_with_vow1 = (*sent1)->vow;
    int start_with_vow2 = (*sent2)->vow;

    return start_with_vow2-start_with_vow1;

}

void sorting(struct Text txt){

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

void the_longest_words(struct Text txt){

    int x, k, j;

    int counter = 0;
    int sent_idx = 0;
    int word_idx = 0;

    for(x = 0; x < txt.count; x++){
        printf("%d ", sent_idx);
        k = 0;
        char *s = txt.sents[x]->str;
        int max_len = 0;
        int len = txt.sents[x]->m;
        for(j = 0; j < len-1; j++){
            if(s[j] != ' ' && s[j] != ',' && s[j] != ';') k++;
            else k = 0;
            if(k > max_len){
                max_len = k;
            }
            word_idx = j;
        }
        sent_idx++;
        printf("%d\n", max_len);
    }
}



int main(){

    setlocale(LC_ALL, "");
    puts("Введите текст. По окончании ввода нажмите клавишу Enter дважды: ");
    struct Text text = readText();
    puts("Выберите опцию:");
    puts("1. Вывести количество слов 'garbage' и результат");
    puts("2. Замена на входное предложение всех цифр в тексте");
    puts("3. Удалить предложения с 3-мя идущими подряд буквами в верхнем регистре");
    puts("4. Отсортировать по уменьшению количества слов начинающихся с гласной буквы");
    puts("5. Найти максимальную длину слова в предложении и вывести строку вида(<номер_предложения> <индекс слова с начала предложения>)");
    puts("6. Выйти из программы\n");
    int a;
    scanf("%d", &a);

    switch(a){
        case(1):
            puts("Result:");
            get_garbage(text);
            break;
        case(2):
            puts("Enter new string:");
            replace_digits(text);
            break;
        case(3):
            puts("Result:");
            delSent(&text);
            break;
        case(4):
            puts("Result:");
            sorting(text);
            break;
        case(5):
            puts("Result:");
            the_longest_words(text);
            break;
        case(6):
            puts("Exiting...");
            break;
        default:
            puts("Such option does not exist!");
            break;
    }

    for(int j = 0; text.count; j++){
        free(text.sents[j]);
    }

    free(text.sents);

    return 0;
}
