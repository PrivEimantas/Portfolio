#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


#define MAX_STRING 128


MYSQL *conn;

int main(int argc, char * argv[])


{
    /*SQL LIB NOT CONNECTED ON RUN, PROJECT->BUILD OPTIONS->LINKER SETTINGS LIBMYSQL.A IN WINGW64
    THEN SEARCH DIRECTORIES LINK 'INCLUDE' FILE FROM LIB
    Establish connection, CHANGE IP TO LOCAL HOST L8ER*/
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "192.168.202.1";
    char *user = "admin";
    char *password = "admin"; /* set me first */
    char *database = "telecom";
    conn = mysql_init(NULL);

    /* If server does not exist terminate*/
    if (mysql_real_connect(conn, "192.168.202.1", "admin", "admin",NULL, 0, NULL, 0) == NULL)
    {
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
    }


    /* CREATE DATABASE IF DOES NOT EXIST*/
    if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS telecom"))
    {
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
    }




    /* Connect to database */
    if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

     //If does not already exists
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS records(id INT PRIMARY KEY, phoneNumber VARCHAR(255),name VARCHAR(255), amount DECIMAL)"))
    {
      finish_with_error(conn);

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
    MYSQL *conn;

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
    input = tolower(input);


    //ONCE USER INPUTS, SELECT WHAT TO DO NEXT
    system("cls");

    //Add record
    if(input == 'a')
    {
        add_record();
    }

    //List records
    if(input=='b'){
        list_records();
    }

    //Modify record
    if(input=='c'){
        //
    }

    //Displays payment
    if(input=='d')
    {
        //
    }

    //Search for a record
    if(input=='e'){
        //
    }

    //Delete record
    if(input=='f'){
        delete_record();
    }

    //User quits program
    if(input=='g')
    {
        exit(1);
    }


    //WHEN INSERTING CHECK MATCHES VALUE IN FIELDS, OTHERWISE NOT INSERTED






}

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}


void add_record()
{
    int id;
    char phoneNumber[11];
    char name[25];
    float amount;

    printf("Selected | Insert Record");
    printf("\n");
    printf("Input id : ");
    scanf("%d",&id);

    printf("\n");
    printf("Input phone number : ");
    scanf("%s",&phoneNumber);

    printf("\n");
    printf("Input name : ");
    scanf("%s",&name);

    printf("\n");
    printf("Input amount : ");
    scanf("%f",&amount);

    // Inserts values into table
    char buf[1024] = {};
    char query_string[] = { "INSERT IGNORE INTO records(id,phoneNumber,name,amount) VALUES(%d,'%s','%s',%.2f)" };
    sprintf(buf, query_string,id,phoneNumber,name,amount);
    if (mysql_query(conn,buf))
    {
      finish_with_error(conn);
    }

    system("cls");
    input_menu();


}

void delete_record()
{
    system("cls");
    int id;

    printf("\n");
    printf("Which record would you like to delete? ");
    printf("\n");
    printf("Specify the ID : ");
    scanf("%d",&id);


    char query[256];
    sprintf(query,"DELETE FROM records WHERE id=%d",id);


    if(mysql_query(conn, query))
    {
        printf("Failed to Delete record successfully\n");

    }




}

void list_records()
{
    system("cls");

    MYSQL_ROW record;
    if (mysql_query(conn, "SELECT * FROM records")) {
        printf("Unable to connect with MySQL server\n");
        mysql_close(conn);
        return 1;
    }

    MYSQL_RES* rs = mysql_store_result(conn);

    if (rs == NULL) {
        printf("Unable to compile SQL statement\n");
        mysql_close(conn);
        return 1;
    }
    printf("\n");
    printf("ID | Phone Number | Name | Amount");
    printf("\n");
    for(int i=0;i<50;i++){
        printf("-");
    }
    while (record = mysql_fetch_row(rs)) {
        printf("%s %s %s %s\n", record[0], record[1], record[2], record[3]);
    }
    for(int i=0;i<50;i++){
        printf("-");
    }
    mysql_close(conn);


}


