#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"tree.h"
#include<stdlib.h>
char menu( void);
void addstudent( Tree *pt,char * arg);
void dropstudent( Tree *pt);
void showstudents( const Tree *pt);
void findstudent( const Tree *pt);
void printitem( Item item);
void uppercase( char *str);
void refresh(const  Tree *pt,char * arg);
void download( char * arg,Tree * pt);
void printftofile( const Node *root,FILE * fp);
int main(int argc,char *argv[] )
{
	Tree students;
	char choice;
	char *arg ;
	arg = argv[1];
	
	if( argc < 2)
	{
		fprintf( stderr,"usage:%s filename\n",argv[0]);
		exit(1);
	}
	puts( "download the data ....");
	InitializeTree( &students);
	download(arg,&students);
	while( ( choice = menu( )) != 'q')
	{
		switch( choice)
		{
			case'a':addstudent( &students,arg);
					break;
			case'l':showstudents( &students);
					break;
			case'f':findstudent( &students);
					break;
			case'n':printf( "%d students in club\n",
							TreeItemCount( &students));
					break;
			case'd':dropstudent( &students);
					break;
			case'r':refresh(&students,arg);
					break;
			default:puts( "switching error");
		}
	}
		DeleteAll( &students);
		puts( "bye.");
		return 0;
}
	char menu( void)
	{
		char ch;
       // char ch1;
		puts( "nerfville student club membership program");
		puts( "enter the letter corresponding to your choice:");
		puts( "a) add a student   l)show list of students");
		puts( "n)number of students f)find students");
		puts( "d)delete a student  q)quit r)reflash");
		while( ( ch = getchar( )) != EOF)
		{

			while( getchar( ) != '\n')
				continue;
			ch = tolower( ch);
			if( strchr("alrfndq",ch) == NULL)
			{	
			printf( "i should not at here %c\n",ch);
			puts( "please enter an a,l,f,n,d,or q:");
			}
			else
				break;

		}
		if( ch == EOF)
			ch = 'q';
		return ch;
	}
	void download( char * arg,Tree * pt)
	{		
		FILE *fp;
		Item temp;
		puts( "i'am download the data");
		if( ( fp = fopen( arg,"a+") ) == NULL)
		{
			fprintf( stderr,"can't create output file\"%s\"\n",arg);
			exit( 2);
		}
			fprintf(stdout, "i'am download the data form\"%s\"\n ",arg);
		while( fgets( temp.studentname,20,fp) != NULL )
		{
			fgets( temp.student_ID,20,fp);		
			uppercase(temp.studentname);
			uppercase(temp.student_ID);	
			AddItem( &temp,pt);
		}
		fclose( fp);
	}
	void showstudents( const Tree * pt)
	{
			if( TreeIsEmpty( pt))
			puts( "no entrise!");
		else
			Traverse( pt,printitem);
	}
	void printitem( Item item)
	{
		printf( "student:%-19s _ID:%-19s\n",item.studentname,item.student_ID);


	}
	void addstudent( Tree * pt,char *arg)
	{
		FILE *fp;
		Item temp;
		if( ( fp = fopen( arg,"r") )== NULL)
		{
			fprintf( stderr,"can't create output file\"%s\"\n",arg);
			exit( 3);
		}
		if( TreeIsFull( pt))
		puts( "no room in the club!");
		else
		{
			puts( "please enter name of student:");
			fgets(temp.studentname,20,stdin);
			fputs(temp.studentname,fp );
			puts( "please enter student _ID:");
			fgets(temp.student_ID,20,stdin);
			fputs( temp.student_ID,fp);
			uppercase(temp.studentname);
			uppercase(temp.student_ID);	
			AddItem( &temp,pt);
		}
		fclose( fp);
	}
	void refresh( const Tree *pt,char * arg)
	{
		FILE *fp;
		 if( ( fp = fopen( arg,"w") )== NULL)
		 {
			fprintf( stderr,"can't create output file\"%s\"\n",arg);
			exit( 3);
		}
		if( TreeIsEmpty( pt))
		puts( "nothing");
		else if( pt != NULL)
			printftofile( pt->root,fp);
		fclose( fp);
	}
	void printftofile( const Node *root,FILE * fp)
	{
		if( root != NULL )
		{
			printftofile( root->left,fp);
			fputs( root->item.studentname,fp);
			fputs( root->item.student_ID,fp);
			printftofile( root->right,fp);
		}	
	}
	void findstudent( const Tree *pt)
	{
		Item temp;

		if( TreeIsEmpty( pt))
		{
			puts("no entrise!" );
			return;
		}
	
	puts("please enter name of student you wish to find:" );
	fgets( temp.studentname,20,stdin);
	puts( "please enter student _ID :");
	fgets( temp.student_ID,20,stdin);
	uppercase( temp.studentname);
	uppercase( temp.student_ID);
	printf( "%s the %s ",temp.studentname,temp.student_ID);
	if( InTree( &temp,pt))
		printf( "is a memeber\n");
	else
		printf( "is not a member.\n");

	}
	void dropstudent( Tree *pt)
	{
		Item temp;
		
		if(TreeIsEmpty( pt) )
		{
			puts( "no entries");
			return ;

		}
		puts( "please enter name of student you wish to delete:");
		fgets( temp.studentname,20,stdin);
		puts( "please enter student_ID");
		fgets( temp.student_ID,20,stdin);
		uppercase( temp.studentname);
		uppercase( temp.student_ID);
		printf( "%s the %s",temp.studentname,temp.student_ID);
		if( DeleteItem( &temp,pt))
			printf( "is droppes from the club.\n");
	}
	void uppercase( char *str)
	{
		while( *str)
		{
			*str = toupper( *str);
			str++;
		}
	}
	




