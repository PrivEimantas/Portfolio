#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


#define MAX_STRING 128


MYSQL *conn;

int main(int argc, char * argv[])


{
    //SQL LIB NOT CONNECTED ON RUN, PROJECT->BUILD OPTIONS->LINKER SETTINGS LIBMYSQL.A IN WINGW64 THEN SEARCH DIRECTORIES LINK 'INCLUDE' FILE FROM LIB
    //Establish connection, CHANGE IP TO LOCAL HOST L8ER

    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.202.1","admin","admin","Telecom",0,NULL,0);

    //Check if connected, if not create DB
    if(conn)
    {
        printf("connected");
    }
    else
    {
        printf("not connected");

        if (mysql_query(conn, "CREATE DATABASE Telecom"))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }
    }

    //If does not already exists
    if (mysql_query(conn, "CREATE TABLE records(id INT PRIMARY KEY, phoneNumber VARCHAR(255),name VARCHAR(255), amount INT)"))
    {
      //
    }


    //SET UP COMPLETE, ASK USER FOR INPUT
    input_menu();






    return 0;
}



void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);
}


void input_menu()
{
    clearScreen();
    char input;

    printf("\n");
    printf("Enter");
    printf("\n");

    printf("A : for adding new records");
    printf("\n");

    printf("B : for list of records");
    printf("\n");

    printf("C : for modifying records");
    printf("\n");

    printf("D : for payment");
    printf("\n");

    printf("E : for searching records");
    printf("\n");

    printf("F : for deleting records");
    printf("\n");

    printf("G : for exit");
    printf("\n");

    scanf("%c",&input);
    input = toupper(input);


    //ONCE USER INPUTS, SELECT WHAT TO DO NEXT
    clearScreen();
    //WHEN INSERTING CHECK MATCHES VALUE IN FIELDS, OTHERWISE NOT INSERTED
    add_record(1,"07472082048","eim",24.99);





}

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}


void add_record(int id, char phoneNumber[],char name[],float amount )
{
    printf("Reaching");
    char query[MAX_STRING];
    snprintf(query, MAX_STRING, "INSERT INTO records (id, phoneNumber,name,amount) VALUES (%d, '%s','%s',%.f2)", id, phoneNumber,name,amount);

    mysql_query(conn, query);
}



