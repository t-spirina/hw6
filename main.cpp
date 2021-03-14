#include <iostream>
#include <fstream>


void fileCreator(std::string &name1, std::string &name2);
void fileUnifier(std::string &name1, std::string &name2);
void fileUnifier(std::string &nameF, std::string &nameS, std::string &nameOUT);
int  getFileSize(std::string &name);
int  findTheWord(std::string &name1, char* word);
void conv(std::string &str);
bool compare(std::string &str , std::string &etalon);

int main(int argc, char* argv[])
{
    //1 Написать программу, которая создаст два текстовых файла, примерно по 50-100 символов в каждом (особого значения не имеет);
    std::string name1,name2,name3;
    name1 = "./first.txt";
    name2 = "./second.txt";
    name3 = "./union.txt";
    fileCreator(name1,name2);

    //2 Написать функцию, «склеивающую» эти файлы, предварительно буферизуя их содержимое в динамически выделенный сегмент памяти нужного размера.
    //так как действия по открыванию файла и считыванию информации в буфер повторяется, то можно выделить в отдельную функцию запись в конец одного
    //файла содержимого второго. Но тогда выделять память будем дважды и больше операций по открытию/закрытию файлов
    //fileUnifier(name1,name3);
    //fileUnifier(name2,name3);
    //Тут все по заданию
    fileUnifier(name1,name2,name3);

    //3* Написать программу, которая проверяет присутствует ли указанное пользователем при запуске программы слово в указанном пользователем файле
    //(для простоты работаем только с латиницей).
    //параметр считываю с консоли
    if (argc>1)
    {
        int count=findTheWord(name3,argv[1]);
        count > 0 ? (std::cout << "количество совпадений - " << count << std::endl) :(std::cout << "нет совпадений" << std::endl);

    }
        return 0;
}

void fileCreator(std::string &name1, std::string &name2)
{
    std::ofstream fileToWrite (name1, std::ios::app);
    if (!fileToWrite)
    {
        std::cout << "файл " << name1 << " не открыт" << std::endl;
        return;
    }
    fileToWrite<< "\
    Friends, Romans, countrymen, lend me your ears\n\
    I come to bury Caesar, not to praise him.\n\
    The evil that men do lives after them;\n\
    The good is oft interred with their bones;\n\
    So let it be with Caesar. The noble Brutus\n\
    Hath told you Caesar was ambitious:\n\
    If it were so, it was a grievous fault, \n\
    And grievously hath Caesar answer’d it. \n\
    Here, under leave of Brutus and the rest– \n\
    For Brutus is an honourable man;\n\
    So are they all, all honourable men– \n\
    Come I to speak in Caesar’s funeral. \n\
    He was my friend, faithful and just to me: \n\
    But Brutus says he was ambitious; \n\
    And Brutus is an honourable man.\n";
    fileToWrite.close();

    fileToWrite.open(name2, std::ios::app);
    if (!fileToWrite)
    {
        std::cout << "файл " << name2 << " не открыт" << std::endl;
        return;
    }
    fileToWrite<< "\
    He hath brought many captives home to Rome\n \
    Whose ransoms did the general coffers fill: \n\
    Did this in Caesar seem ambitious? \n\
    When that the poor have cried, Caesar hath wept:\n\
    Ambition should be made of sterner stuff: \n\
    Yet Brutus says he was ambitious; \n\
    And Brutus is an honourable man. \n\
    You all did see that on the Lupercal \n\
    I thrice presented him a kingly crown, \n\
    Which he did thrice refuse: was this ambition? \n\
    Yet Brutus says he was ambitious; \n\
    And, sure, he is an honourable man. \n\
    I speak not to disprove what Brutus spoke, \n\
    But here I am to speak what I do know. \n\
    You all did love him once, not without cause: \n\
    What cause withholds you then, to mourn for him? \n\
    O judgment! thou art fled to brutish beasts, \n\
    And men have lost their reason. Bear with me; \n\
    My heart is in the coffin there with Caesar, \n\
    And I must pause till it come back to me.";
}

void fileUnifier(std::string &nameIN, std::string &nameOUT)
{
//в конец файла nameOUT записывает содержимое файла nameIN
    int size;
    int i=0;
    std::ifstream fileToRead;
    std::ofstream fileToWrite;
    size=getFileSize(nameIN)+1;
    std::cout<<"size= "<<(size)<<std::endl;
    char* file1 = new char[size];
    fileToRead.open(nameIN);
    if (!fileToRead)
    {
        std::cout << "файл " << nameIN << " не открыт" << std::endl;
        delete [] file1;
        return;
    }
    while(!fileToRead.eof())
    {
      fileToRead.get(file1[i]);
      printf("%c",file1[i]);
      i++;
    }
    fileToRead.close();
    std::cout<<"i=  "<<i << "size="<<(size)<<std::endl;
    fileToWrite.open(nameOUT,std::ios::app);
    if (!fileToWrite)
    {
        std::cout << "файл " << nameOUT << " не открыт" << std::endl;
        delete [] file1;
        return;
    }
    fileToWrite<<file1;
    fileToWrite.close();
    delete [] file1;
}
void fileUnifier(std::string &nameF, std::string &nameS, std::string &nameOUT)
{
//дописывает в файл nameOUT сначала содержимое файла nameF, затем файла nameS
    int size;
    int i = 0;
    std::ifstream fileToRead;
    std::ofstream fileToWrite;
    size = getFileSize(nameF) + getFileSize(nameS) + 1;

    char* file1 = new char[size];
    fileToRead.open(nameF);
    if (!fileToRead)
    {
        std::cout << "файл " << nameF << " не открыт" << std::endl;
        delete [] file1;
        return;
    }

    while(!fileToRead.eof())
    {
      fileToRead.get(file1[i]);
      i++;
    }
    i--;
    fileToRead.close();
    fileToRead.open(nameS);
    if (!fileToRead)
    {
        std::cout << "файл " << nameS << " не открыт" << std::endl;
        delete [] file1;
        return;
    }
    while(!fileToRead.eof())
    {
      fileToRead.get(file1[i]);
      i++;
    }
    fileToRead.close();
    fileToWrite.open(nameOUT,std::ios::app);
    if (!fileToWrite)
    {
        std::cout << "файл " << nameOUT << " не открыт" << std::endl;
        delete [] file1;
        return;
    }
    fileToWrite<<file1;
    fileToWrite.close();
    delete [] file1;
}

int  getFileSize(std::string &name)
{
    int size;
    std::ofstream fileToOpen;
    if (!fileToOpen)
    {
        std::cout << "файл " << name << "не открыт" << std::endl;
        return 0;
    }
    fileToOpen.open(name,std::ios::app);
    size = fileToOpen.tellp();
    fileToOpen.close();
    return size;
}

int  findTheWord(std::string &name1, char* word)
{
    std::ifstream fToRead;
    std::string str = word;
    std::string fileWord;

    int count = 0;
    fToRead.open(name1);
    if (!fToRead)
        return 0;
    conv(str);
    while(!fToRead.eof())
    {
        fToRead >> fileWord;
        if (compare(fileWord, str))
            count++;
    }
    fToRead.close();
    return count;
}


void conv(std::string &str)
{
    for(int i=0;str[i]!=0;i++)
    {
        if(str[i] <= 'z' && str[i] >= 'a')
            str[i] -= 32;
    }
}
bool compare(std::string &str, std::string &etalon)
{
    for(int i = 0; etalon[i] !=0 ; i++)
    {
        if (str[i]==0) return false;
        if (str[i] <= 'z' && str[i] >= 'a')
            str[i] -= 32;
        if(str[i] != etalon[i])
            return false;
    }
    return true;
}
