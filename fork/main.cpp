#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<unistd.h>

int f1()
{
    return 1;
}

int f2()
{
    return 0;
}

int f3()
{
    return -1;
}


int (*f[])() = { &f1, &f2, &f3};

void write_in_file(std::ofstream & of, int i, const std::string& result)
{
    of << "f" << i << " function - " <<  result << std::endl;
}

int main()
{

    int j = 0;    
    std::ofstream of;
    of.open("result.txt");    
    of << "Test results:" << std::endl;
    for(int i = 0; i < 3; ++i)
    {
        pid_t pid = fork();
        if(pid == 0)
        {   
            int res = f[i]();
            if(res == 0)
            {
                write_in_file(of, i, "Success");
                exit(EXIT_SUCCESS);
            }
            else if(res == 1)
            {
                write_in_file(of, i, "Failure");
                exit(EXIT_SUCCESS);
            }
            else
            {
                write_in_file(of, i, "Unresolved");
                exit(EXIT_SUCCESS);
            }
        }
    }
    of.close();
    return 0;
}
