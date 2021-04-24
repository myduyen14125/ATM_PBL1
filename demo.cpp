#include<bits/stdc++.h>
using namespace std;

void menu();
bool login();
int  check(long long Ac,long long Mp);
int  Option();
int  RutTien();
int  NapTien();
void XemTaiKhoan();
void LuuGD(int opt,int rut,int nap);

int rut,nap,x=0,n=0;
long long taikhoan[100],mapin[100],sotien[100];

int main()
{
	menu();
	if(login()==1)
	{
	z:	int opt=Option();
		switch (opt)
		{
			case 1:
				{
					int rut=RutTien();
					cout<<"Ban co muon giao dich tiep khong ?"<<endl;
					goto z;
					break;
				}
			case 2:
				{
					int nap=NapTien();
					cout<<"Ban co muon giao dich tiep khong ?"<<endl;
					goto z;
					break;
				}
			case 3:
				{
					XemTaiKhoan();
					cout<<"Ban co muon giao dich tiep khong ?"<<endl;
					goto z;
					break;
				}
			case 4:
				{
					return 0;
				}
				
		}
		LuuGD(opt,rut,nap);
	}
	return 0;
}

void menu()
{
	cout<<"+----------------------------------------------------------+"<<endl;
	cout<<"'                     WELCOME TO ATM DT                    '"<<endl;
	cout<<"'               SV:   Nguyen Tran My Duyen                 '"<<endl;
	cout<<"'                     Nguyen Phuoc Dai Toan                '"<<endl;
	cout<<"'             GVHD:   Tran Ho Thuy Tien                    '"<<endl;
	cout<<"+----------------------------------------------------------+"<<endl;
	cout<<endl;
}

bool login()
{	int dem=1;
	long long account, mapin;
	while(dem<=5)
	{
		cout<<"Nhap account	: ";
		cin>>account;
		cout<<"Ma Pin		: ";
		cin>>mapin;
		if(check(account,mapin)==1)	return 1;
		else
		{
			if(dem==5)		cout<<"Tai Khoan Cua Ban Da Bi Khoa"<<endl;
			else 
			{
				cout<<"_____________________"<<endl;
				cout<<"Tai khoan hoac mat khau cua ban khong dung !!!"<<endl;
				cout<<"Ban con so lan nhap la: "<<5-dem<<endl;
				cout<<"Vui long nhap lai !!!"<<endl;
				cout<<"_____________________"<<endl;
			}
		}
		dem++;
	}
	return 0;

}

int check(long long Ac,long long Mp)
{
	ifstream FileIn;
	FileIn.open("ThongTin.txt",ios_base::in);

	int i=1;
	
	while(!FileIn.eof())
	{
		FileIn>>taikhoan[i];
		FileIn>>mapin[i];
		FileIn>>sotien[i];
		if(Ac==taikhoan[i] && Mp==mapin[i]) x=i;
		i++;
	}
	n=i-2;
	FileIn.close();
	if (x!=0) return 1;
	return 0;
}
int Option()
{
	int nhap;
	do
	{
		cout<<"___________MENU___________"<<endl;
		cout<<"1. Rut tien."<<endl;
		cout<<"2. Nap tien."<<endl;
		cout<<"3. Xem tai khoan."<<endl;
		cout<<"4. Exit"<<endl;
		cout<<"Vui long chon giao dich: ";
		cin>>nhap;
	} 
	while (nhap>4);
	return nhap;
}

int RutTien()
{
	cout<<"Nhap so tien ban can rut: ";
	cin>>rut;
	if(rut>sotien[x]) cout<<"So tien cua ban khong du de thuc hien giao dich nay !!!"<<endl;
	else 
	{
		cout<<"Giao dich thanh cong !!!"<<endl;
		sotien[x]-=rut;
	}
	return rut;
}

int NapTien()
{
	cout<<"Nhap so tien ban can nap: ";
	cin>>nap;
	cout<<"Giao dich thanh cong !!!"<<endl;
	sotien[x]+=nap;
	return nap;
}

void XemTaiKhoan()
{
	cout<<"Tai khoan cua ban hien tai la: "<<sotien[x]<<endl;
}

void LuuGD(int opt,int rut,int nap)
{
	time_t now = time(0);
   	char* dt = ctime(&now);
   	
	int i=1;
	ofstream FileOut;
	FileOut.open("ThongTin.txt",ios_base::out);
	while(i<=n)
	{
		FileOut<<taikhoan[i]<<"			"<<mapin[i]<<"			"<<sotien[i]<<endl;
		i++;
	}
	FileOut.close();
	ofstream FileGD;
	FileGD.open("ThongTin.txt",ios_base::app);
	if(opt==1)			FileGD<<taikhoan[x]<<"			"<<"-"<<rut<<"			"<<dt<<endl;
	else if(opt==2)		FileGD<<taikhoan[x]<<"			"<<"+"<<nap<<"			"<<dt<<endl;
	else 				FileGD<<taikhoan[x]<<"			"<<"Xem tai khoan"<<"			"<<dt<<endl;
}

	

	
