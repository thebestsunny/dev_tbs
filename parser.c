#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

char input[256] = {0};
char output[256] = {0};
char* words[256] = {0};

int size = 0;
int oitt = 0;

bool CheckTokens()
{
    int i;
    for(i=0; i<size; i++)
    {
        if(!Verb(words[i]) && !Noun(words[i]) && !Adj(words[i]) && !Adv(words[i]) && !Prep(words[i]))
        {
            return false;
        }
    }
    return true;
}

void SplitStr(char*str)
{
    char* p;
    p = strtok(str, " ");

    int i = 0;
    while(p)
    {
        words[i] = (char*)malloc(strlen(p)+1);
        strcpy(words[i],p);
        p = strtok(NULL, " ");
        i++;
    }

    size = i;
}

bool Verb(char* word)
{
    if(strcmp(word,"lifted") != 0 && strcmp(word,"saw") != 0 && strcmp(word,"found") != 0)
    {
        return false;
    }
    return true;
}

bool Noun(char* word)
{
    if(strcmp(word,"cow") != 0 && strcmp(word,"alice") != 0 && strcmp(word,"book") != 0)
    {
        return false;
    }
    return true;
}

bool Adv(char* word)
{
    if(strcmp(word,"quickly") != 0 && strcmp(word,"carefully") != 0 && strcmp(word,"brilliantly") != 0)
    {
        return false;
    }
    return true;
}

bool Adj(char* word)
{
    if(strcmp(word,"green") != 0 && strcmp(word,"lean") != 0 && strcmp(word,"mean") != 0)
    {
        return false;
    }
    return true;
}

bool Prep(char* word)
{
    if(strcmp(word,"of") != 0 && strcmp(word,"at") != 0 && strcmp(word,"with") != 0)
    {
        return false;
    }
    return true;
}

void PushLeftKuo()
{
    output[oitt++] = '(';
}

void PushRightKuo()
{
    output[oitt++] = ')';
}

void PopLeftKuo()
{
    oitt--;
}

void PushSpace()
{
    output[oitt++] = ' ';
}

void PutWord(char* word)
{
    output[oitt++] = '"';
    strcpy(&output[oitt], word);
    oitt += strlen(word);
    output[oitt++] = '"';
}

bool VerbPhrase(int* itt)
{
    if(*itt >= size) return false;

    PushLeftKuo();
    if(Verb(words[*itt]))
    {
        PutWord(words[*itt]);
        (*itt)++;
        if(Adv(words[*itt]))
        {
            PutWord(words[*itt]);
            (*itt)++;
        }
    }
    else
    {
        PopLeftKuo();
        return false;
    }
    PushRightKuo();
}

bool AdjPhrase(int* itt)
{
    if(*itt >= size) return false;

    PushLeftKuo();
    if(Adj(words[*itt]))
    {
        PutWord(words[*itt]);
        int ti = *itt + 1;
        (*itt)++;
        if(AdjPhrase(&ti))
        {
            *itt = ti;
        }
    }
    else
    {
        PopLeftKuo();
        return false;
    }
    PushRightKuo();
}

bool PrepPhrase(int* itt)
{
    if(*itt >= size) return false;

    PushLeftKuo();
    if(Prep(words[*itt]))
    {
        PutWord(words[*itt]);
        int ti = *itt + 1;
        (*itt)++;
        if(NounPhrase(&ti))
        {
            *itt = ti;
        }
    }
    else
    {
        PopLeftKuo();
        return false;
    }
    PushRightKuo();

}

bool NounPhrase(int* itt)
{
    if(*itt >= size) return false;

    PushLeftKuo();
    if(Noun(words[*itt]))
    {
        PutWord(words[*itt]);
        int ti = *itt + 1;
        (*itt)++;
        if(PrepPhrase(&ti))
        {
            *itt = ti;
        }
    }
    else
    {
        if(AdjPhrase(itt))
        {
            if(Noun(words[*itt]))
            {
                PutWord(words[*itt]);
                int ti = *itt + 1;
                (*itt)++;
                if(PrepPhrase(&ti))
                {
                    *itt = ti;
                }
            }
            else
            {
                PopLeftKuo();
                return false;
            }
        }
        else
        {
            PopLeftKuo();
            return false;
        }
    }
    PushRightKuo();
    return true;
}

bool Sentence(int* itt)
{
    PushLeftKuo();
    if(!NounPhrase(itt))
    {
        return false;
    }
    
    PushSpace();
    
    if(!VerbPhrase(itt))
    {
        return false;
    }

    PushSpace();

    if(!NounPhrase(itt))
    {
        return false;
    }

    PushRightKuo();
    return true;
}


int main()
{
    gets(input);

    SplitStr(input);

    if(!CheckTokens(words))
    {
        printf("invalid token\n");
        return -1;
    }

    int itt = 0;
    
    if(!Sentence(&itt))
    {
        printf("invalid sentence\n");
    }
    else
    {
        printf("%.*s\n", ++oitt, output);
    }
}
