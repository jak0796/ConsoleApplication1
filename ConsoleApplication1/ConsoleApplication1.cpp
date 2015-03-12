#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include<stdlib.h>
#include<io.h>
#pragma warning(disable: 4996)
using namespace std;
struct item
{
	char name[10];// ������������.
	char value[10];// ���������� �������
	int  number;// ����� ����
};
struct item it[10];// ������ ��������.
int count = 0;// ���������� ��������
char fname[20];// �������� �����.
// ������� //
// ������ � ������//
void filename();
void newFile();// �������� �����
void viewFile();// �������� ����������� �����+
void addFile();// ���������� ����� ������ �� �������+
void editFile();// ��������� ������� �� �������+
void deleteRecord();
void runFile();// ���������� �� �������� +
void rewrite();
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	printf("0-open file\n");
	printf("1-Sozdanie faila\n");
	printf("2-prosmotr faila\n");
	printf("3-dobavlenie\n");
	printf("4-izmenie zapisi\n");
	printf("5-ydalenie\n");
	printf("6-sortirovka\n");
	for (;;)
	{
		int choise;
		cin >> choise;
		switch (choise)
		{
		
		case 1:newFile(); break;
		case 2:viewFile(); break;
		case 3:addFile(); break;
		case 4:editFile(); break;
		case 5:deleteRecord(); break;
		case 6:runFile(); break;
		default:cout << "Nazmite  Pravilno(1-6)"; break;
		}
		printf("Vvedite nomer operacii ili 0-Dla vuhoda\n");
		if (choise == 0)break;
	}
	_getch();
	return 0;
}


void rewrite()
{
	FILE *f, *s;
	f = fopen(fname, "w"); s = fopen(fname, "r+");
	struct item t;
	int g = 0;
	while (true)
	{
		int c;
		c = fread(&t, sizeof(item), 1, s);
		if (c != 1)break;
		it[g] = t;
		fwrite(&it[g], sizeof(item), 1, f);
		g++;
	}
	fclose(f); fclose(s);
}
void filename()
{
	int j = 0;// �������
	cout << "Vvedite nazvanie faila" << endl;
	cin >> fname;

}
void newFile()
{
	filename();
	FILE *f;
	if (!(f = fopen(fname, "w+b")))// ������� ���� �� ���������� ������
	{
		puts("File error");
	}
	else
	{
		cout << "File sozdan" << endl;
		fclose(f);
	}
}
void viewFile()
{
	FILE *f;
	struct item t;
	if (!(f = fopen(fname, "r")))// �������� ����� ����� ����� ��� �����
	{
		puts("File error");
	}
	else
	{
		int n = 0;// ���������� ������ � �����
		int i = 0;
		puts("Prosmotr Dannih");
		while (true)
		{
			int z;
			z = fread(&t, sizeof(item), 1, f);
			if (z != 1)break;
			it[n] = t;
			cout << "Nazvanie:" << it[n].name << endl;
			cout << "Kol-vo:" << it[n].value << endl;
			cout << "Nomer Ceha:" << it[n].number << endl;
			n++;
		}
		fclose(f);
	}
};
void addFile()
{
	int count = 0;
	FILE *f;
	puts("Kakoe koli4esto detalei vu hotite dobavit");
	int k = 0;
	cin >> k;
	int i;
	if (!(f = fopen(fname, "a+b")))
	{
		puts("File error");
	}
	else
	{
		for (i = 0; i<k; i++)
		{
			printf("Vvedite Nazvanie zap4asti\n");
			scanf("%s", &it[i].name);
			printf("Vvedite Kol-vo zap4asti %s\n", it[i].name);
			scanf("%s", &it[i].value);
			printf("Vvedite nomer ceha\n");
			scanf("%d", &it[i].number);
			fwrite(&it[i], sizeof(item), 1, f);// ������ � ���� ������ ���������.
			count++;
		}
		fclose(f);
	}
}
void runFile(void)
{
	FILE *f;
	int i, j;
	struct item t;
	if (!(f = fopen(fname, "r+b")))
	{
		puts("File error");
	}
	else
	{
		printf("Dannie v faile\n");
		int n = 0;// ���������� �������
		int m[10];
		while (true)
		{
			int n1 = fread(&t, sizeof(item), 1, f);// ������
			if (n1 != 1)break;
			it[n] = t;
			cout << "Nazvanie detali:" << it[n].name;
			cout << "Kol-vo detalei:" << it[n].value;
			cout << "Nomer ceha:" << it[n].number << endl;
			m[n] = atoi(it[n].value);
			n++;
		}
		cout << "Koli4estvo detalei do sortirovki" << endl;
		for (i = 0; i<n; i++)
			cout << m[i] << endl;// ����� ���������� ������� ���� �� ����������.
		if (feof(f))cout << "Konec faila" << endl;
		for (i = 0; i<n - 1; i++)
		{
			for (j = i + 1; j<n; j++)
			if (m[i]<m[j]) // ���������� �� �������� ���������� �������.
			{
				struct item temp;
				temp = it[i];
				it[i] = it[j];
				it[j] = temp;
			}
		}
		printf("Dannie v faile posle sortirovki\n");
		for (i = 0; i<n; i++)
		{
			cout << "Nazvanie detali:";
			cout << it[i].name;
			cout << "Kol-vo:";
			cout << it[i].value;
			cout << "Nomer ceha:";
			cout << it[i].number << endl;
			fseek(f, sizeof(item)*(i), SEEK_SET);// ������������� �������
			fwrite(&it[i], sizeof(item), 1, f);
		}
		fclose(f);
	}
}
void editFile()
{
	FILE *f;
	struct item it1;
	int n = 1;
	if (!(f = fopen(fname, "r+b")))// ������ �����
	{
		puts("File error");
	}
	else
	{
		fseek(f, 0, SEEK_END);
		int a = 0;// ����� ��������������/
		int records = ftell(f) / sizeof(item);
		while (true)
		{
			puts("Vvedite Poziciu korrektirovki");
			scanf("%d", &a);
			if (a<0 || a>records)break;
			fseek(f, sizeof(item)*(a - 1), SEEK_SET);
			if (sizeof(item) != fread(&it1, 1, sizeof(item), f))
				puts("Konec faila");
			else
				it[n] = it1;
			printf("Detal:%sKol-vo:%sNomer ceha:%s\n", it[n].name, it[n].value, it[n].number);
			puts("Vvedite korrektirovki Nomera ceha\n");
			scanf("%d", &it[n].number);
			puts("Dannie posle korrektirovki\n");
			printf("%s%s%d\n", it[n].name, it[n].value, it[n].number);
			fseek(f, sizeof(item)*(a - 1), SEEK_SET);// ?
			fwrite(&it[n], sizeof(item), 1, f);
			n++;
		}
		fclose(f);
	}
}
void deleteRecord(void)
{
	FILE *f, *s;
	int c;
	int h;
	int g;// �������
	if (!(f = fopen(fname, "r+b")))
	{
		puts("File error");
	}
	else
	{
		s = fopen("new.txt", "a+t");// ���� ��� ���������� �������� ������
		cout << "Vvedite nomer ceha dla ydaleniya detali" << endl;
		cin >> h;
		while (1)
		{
			g = 0;
			c = fread(&it[g], sizeof(item), 1, f);
			if (!c)break;
			if (it[g].number != h)
				fwrite(&it, sizeof(item), 1, s);
			g++;
		}
		rewrite();
		fclose(s); fclose(f);
	}
}