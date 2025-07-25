﻿#include <iostream>
using namespace std;
#include <string>
#include <ctime>

class You {
private:
	int birth;
	string id, password;
	char men;
public:
	You() : birth(14430101), id("HongGilDong"), password("password"), men('M') {} // 기본 생성자
	You(int a, string i, string p, char m): birth(a), id(i), password(p), men(m){} // 일반 생성자

	int getbirth() { return birth; }
	string getid() { return id; }
	string getpass() { return password; }
	int getmen(); // 성별을 주민등록번호 뒷자리의 첫 숫자로 변경한 후, 반환

}; // 사용자의 개인정보를 저장하는 클래스

int You::getmen() {
	int meni;
	if (birth >= 10000000 && birth < 20000000) {
		if (men == 'M')
			meni = 1;
		if (men == 'W')
			meni = 2;
		else {
			cout << "성별을 잘못 입력하셨습니다." << endl;
			meni = 0;
		}
	}
	else if (birth >= 20000000) {
		if (men == 'M')
			meni = 3;
		if (men == 'W')
			meni = 4;
		else {
			cout << "성별을 잘못 입력하셨습니다." << endl;
			meni = 0;
		}
	}
	else {
		cout << "생년월일을 잘못 입력하셨습니다. 임시로 지갑을 생성합니다." << endl;
		meni = 0;
	}
	return meni;
}



class DigitalSign : public You{
private:
	string digitalsign;
	string birthmen;
public:
	DigitalSign() {
		You hong;
		birthmen = "144301011";
		digitalsign = hong.getid() + hong.getpass() + birthmen;
		// 만약 hong이라는 기본 생성자에 접근 지정자를 붙이지 않게 되면
		// DigitalSign의 기본 생성자 즉 자기 자신에 접근하여 메서드 getid(), getpass()를 수행한다.
	} // 기본 생성자

	DigitalSign(int a, string i, string p, char m): You(a, i, p, m) {
		birthmen = to_string(getbirth()) + to_string(getmen());
		// int형인 생년월일과 성별을 일렬로 나란히 연결하여 문자열 birthmen에 저장
		digitalsign = getid() + getpass() + birthmen;
	} // 일반 생성자

	string getDS() { return digitalsign; }
};



class Wallet : public DigitalSign { 
private:
	int publickey = 10101;
	int privatekey;
	int dollar;
	int hash = 5381;
	string ds;
public:
	Wallet(): privatekey(5381), dollar(50000), ds("HongGilDongpassword144301011") {} // 기본 생성자
	Wallet(int a, string i, string p, char m): DigitalSign(a, i, p, m) {
		dollar = 0;
		ds = DigitalSign::getDS();
		hash = gethash();
		privatekey = getpk();
	} // 일반 생성자

	void first(string i) {
		cout << i << "님의 지갑에 최초로 접근합니다." << endl;
		cout << "디지털 서명: " << ds << endl;
		cout << "공개키: 10101, 개인키: " << privatekey << endl;
		cout << "해시값: " << hash << "입니다." << endl;
	} // 최초로 지갑 생성 시 기본 정보 출력

	int gethash(); // 해시값을 생성한 후, 반환
	int getpk(); // 개인키를 생성한 후, 반환

	void info(int a, string i, string p, char m); // 1. 내 정보 보기
	void charge(int a, string i, string p, char m); // 2. 지갑 충전하기
	void pay(Wallet w); // 3. 거래하기
	void Honginfo();
	int getdollar() { return dollar; };
};
int Wallet::gethash() {
	for (char c : ds) {
		hash = hash * 33 + c;
	} // 5381로 초기화된 해시값에 각 문자에 대해 33을 곱하고 마지막에 해당 문자의 ASCII 코드를 더한다
	return hash;
}
int Wallet::getpk() {
	privatekey = hash % 100000;
	while (privatekey >= 10101) 
		privatekey -= 101;
	
	while (privatekey < 0)
		privatekey += 10101; 
	// 개인키를 양수로 제한

	return privatekey;
}

void Wallet::info(int a, string i, string p, char m) {
	You you(a, i, p, m);
	string iid, ppass;
	int ppk;

	cout << "아이디를 입력해주세요: ";
	cin >> iid;
	for (int i = 0; iid != you.getid() && i < 3; i++) {
		cout << "유효하지 않은 아이디입니다." << endl;
		cout << "아이디를 재입력해주세요(남은 횟수 " << 3-i << "번): ";
		cin >> iid;
		if (i > 2)
			exit(1);
	}

	cout << "비밀번호를 입력해주세요: ";
	cin >> ppass;
	for (int i = 0; ppass != you.getpass() && i < 3; i++) {
		cout << "잘못된 비밀번호입니다." << endl;
		cout << "비밀번호를 재입력해주세요(남은 횟수 " << 3 - i << "번): ";
		cin >> ppass;
		if (i > 2)
			exit(1);
		}

	cout << "개인키를 입력해주세요: ";
	cin >> ppk;
	for (int i = 0; ppk != privatekey && i < 3; i++) {
		cout << "잘못된 개인키입니다." << endl;
		cout << "개인키를 재입력해주세요(남은 횟수 " << 3 - i << "번): ";
		cin >> ppk;
		if (i > 2)
			exit(1);
	}

	cout << "=====================" << endl;
	cout << you.getid() << "님의 지갑입니다." << endl;
					// Wallet이 상속한 You의 메서드에 직접적으로 명시하여 접근
	cout << "공개키: 10101" << endl;
	cout << "개인키: " << privatekey << endl << "해시값: " << hash << endl << "잔액: " << dollar << "원" << endl;
    }

void Wallet::charge(int a, string i, string p, char m) {

	You you(a, i, p, m);

	int ppk;
	cout << "개인키를 입력해주세요: ";
	cin >> ppk;
	for (int i = 0; ppk != privatekey && i < 3; i++) {
		cout << "잘못된 개인키입니다." << endl;
		cout << "개인키를 재입력해주세요(남은 횟수 " << 3 - i << "번): ";
		cin >> ppk;
		if (i > 2)
			exit(1);
	}

	if (privatekey == ppk) {
		cout << you.getid() << "님의 지갑입니다." << endl;
		cout << "공개키: 10101, 개인키: " << privatekey << ", 해시값: " << hash << ", 잔액: " << dollar << "원 입니다." << endl;

		cout << "얼마를 충전하시겠습니까? ";
		cin >> dollar;
		cout << endl << dollar << "원을 충전하셨습니다." << endl;

	}
}

void Wallet::pay(Wallet w) {

	int ppk;
	cout << w.You::getid() << "님의 개인키를 입력해주세요: ";
	cin >> ppk;
	for (int i = 0; ppk != privatekey && i < 3; i++) {
		cout << "잘못된 개인키입니다." << endl;
		cout << "개인키를 재입력해주세요(남은 횟수 " << 3 - i << "번): ";
		cin >> ppk;
		if (i > 2)
			exit(1);
	}

	if (privatekey == ppk) {
		cout << w.You::getid() << "님의 지갑입니다." << endl;
		cout << "공개키: 10101" << endl << "개인키: " << privatekey << endl << "해시값: " << hash << endl;
		cout << "잔액: " << dollar << "원 입니다." << endl;

		char c;
		cout << "지갑을 먼저 충전하시겠습니까?(Y / N) ";
		cin >> c;
		if (c == 'Y' || c == 'y')
			w.charge(w.You::getbirth(), w.You::getid(), w.You::getpass(), w.You::getmen());

		int menu, money;
		Wallet Hong;
		cout << "돈을 송금하시려면 1번을, 돈을 받으시려면 2번을 눌러주세요: ";
		cin >> menu;
		switch (menu) {
		case 1:
			cout << "HongGilDong 님의 지갑에 얼마를 송금하시겠습니까? ";
			cin >> money;
			w.dollar -= money;
			Hong.dollar += money;
			break;
		case 2:
			int pk;
			cout << "HongGilDong님의 개인키를 입력해주세요: " << endl;
			cin >> pk;
			for (int i = 0; pk != Hong.privatekey && i < 3; i++) {
				cout << "잘못된 개인키입니다." << endl;
				cout << "개인키를 재입력해주세요(남은 횟수 " << 3 - i << "번): ";
				cin >> pk;
				if (i > 2)
					exit(1);
			}
			if (pk == Hong.privatekey) {
				cout << "HongGilDong님의 지갑에 접근을 허용합니다." << endl;
				cout << w.You::getid() << "님의 지갑에 얼마를 송금하시겠습니까? ";
				cin >> money;
				if (money > 50000) {
					cout << "잔액이 부족합니다." << endl;
					break;
				}
				w.dollar += money;
				Hong.dollar -= money;
			}
			break;
		default:
			cout << "잘못 입력하셨습니다." << endl ;
		}

		cout << w.You::getid() << "님의 잔액: " << w.dollar << endl;
		if (w.dollar < 0)
			cout << w.dollar << "의 빚을 갚으셔야합니다." << endl;
		cout << "HongGilDong님의 잔액: " << Hong.dollar << endl;
	}
}

void Wallet::Honginfo() {
	Wallet hong;
	cout << "아이디: " << hong.You::getid() << endl;
	cout << "생년월일: " << hong.You::getbirth() << endl;
	cout << "비밀번호: " << hong.You::getpass() << endl;
	// You:: 클래스 내의 메서드에 접근한다고 명시해둔 이유는
	// Wallet 클래스가 You뿐만 아니라 DigitalSign 클래스도 다중 상속받았기 때문이다.
	// DigitalSign 클래스 자체도 You 클래스로부터 상속받은 것이므로,
	// Wallet -> You 뿐만 아니라
	// Wallet -> DigitalSign -> You 이렇게 두 방향을 이용해 You에 접근할 수 있기에
	// 명시하지 않으면 모호하다며 오류가 발생
	cout << "개인키: " << hong.privatekey << endl;
	cout << "금액: " << hong.getdollar() << endl;
}


int menu() {
	cout << endl << "메뉴:" << endl;
	cout << "1. 내 정보 보기" << endl << "2. 지갑 충전하기" << endl;
	cout << "3. 거래하기" << endl << "9. 도움말" << endl;
	cout << "0. 프로그램 종료" << endl;

	cout << "메뉴 번호를 입력해주세요: ";
	int menu;
	cin >> menu;
	return menu;
}

void help() {
	cout << "---------------------------------------" << endl;
	cout << "사용자님의 아이디는 영문성함과 같습니다." << endl << endl;
	cout << "생년월일 혹은 성별을 제대로 기입하지 않았다면 자동으로 생성된 지갑 및 디지털 서명은 임시적인 것입니다." << endl
		<< "더욱 정확한 고유의 지갑을 생성하기 위해선 프로그램을 처음부터 다시 시작해주세요." << endl << endl;

	int m;
	cout << "어떤 메뉴의 도움말이 필요하신가요?" << endl;
	cout << "1. 내 정보 보기" << endl << "2. 지갑 충전하기" << endl << "3. 거래하기" << endl;
	cin >> m;
	switch (m){
	case 1:
		cout << "1. 내 정보 보기 메뉴 에서는" << endl
			<< "프로그램 시작 시 입력했던 영문성함과 비밀번호, 그리고 지갑에 최초 접근했을 때 자동으로 출력된 개인키를 입력하면" << endl
			<< "지갑 주인의 이름, 공개키, 개인키, 해시값과 잔액을 출력합니다." << endl << endl;
		break;
	case 2:
		cout << "2. 지갑 충전하기 메뉴 에서는" << endl
			<< "개인키만을 입력하면" << endl
			<< "지갑 주인의 이름, 공개키, 개인키, 해시값과 잔액을 출력합니다." << endl
			<< "얼마를 충전하시겠습니까? 라는 물음에 충전하고자 하는 금액을 입력하면 됩니다." << endl << endl;
		break;
	case 3:
		cout << "3. 거래하기 메뉴 에서는" << endl
			<< "거래 상대방인 HongGilDong님의 지갑 정보를 먼저 출력합니다." << endl;
		cout << "개인키만을 입력하면" << endl
			<< "지갑 주인의 이름, 공개키, 개인키, 해시값과 잔액을 출력합니다." << endl
			<< "거래를 진행하기 전, 지갑을 먼저 충전하시겠습니까? 라는 물음에 충전을 원하시면 Y를, 그렇지 않다면 N을 입력하면 된다." << endl;
		cout << "거래는 총 2가지: 본인의 지갑에서 홍길동 지갑으로 돈을 송금, 또는 홍길동 지갑에서 본인의 지갑으로 돈을 받는 거래이다." << endl
			<< "돈을 송금하려면 1번을 눌러," << endl
			<< "본인의 지갑에서 얼마를 보낼 것인지 입력한다." << endl;
		cout << "돈을 홍길동으로부터 받기 위해서는," << endl
			<< "홍길동 지갑에 접근을 할 수 있어야 하므로," << endl
			<< "앞서서 출력된 홍길동님의 개인키를 입력하여 본인의 지갑으로 얼마를 보낼 것인지 입력한다." << endl;
		cout << "거래가 완료되면, 본인 지갑의 잔액과 홍길동님 지갑의 잔액을 출력한다." << endl
			<< "거래 도중 본인 지갑의 잔액이 부족할 경우, 빚을 갚아야한다는 문구가 출력된다." << endl;
		break;
	default:
		cout << "도움말 메뉴를 나갑니다." << endl;
	}
	cout << "---------------------------------------" << endl << endl;
}

void main() {
	cout << "코인 거래소에 오신 걸 환영합니다." << endl;
	
	cout << "회원가입을 시작합니다." << endl;
	int birth;
	string id, password;
	char men;
	cout << "생년월일을 입력해주세요(14430101): ";
	cin >> birth;
	cout << "성함을 입력해주세요(영문으로, 띄어쓰기 없이): ";
	cin >> id;
	cout << "비밀번호를 입력해주세요: ";
	cin >> password;
	cout << "성별을 입력해주세요(남성이면 M, 여성이면 W): ";
	char mm;
	cin >> mm;
	if (mm >= 'a' && mm <= 'z') {
		mm -= 32;
	}
	men = mm;
	if (mm != 'W' && mm != 'M') {
		cout << "성별을 잘못 입력하셨습니다." << endl;
	}

	
	Wallet wuser(birth, id, password, men);
	wuser.first(id);
	Wallet Hong; // 기본 생성자이자 거래 상대방
	             // 기본 생성자이기 때문에 괄호 사용 불가능

	int no;

	while (1) {
		no = menu();

		switch (no) {
		case 1:
			cout << "1. 내 정보 보기 메뉴를 선택하셨습니다." << endl;
			wuser.info(birth, id, password, men);
			break;
		case 2:
			cout << "2. 지갑 충전하기 메뉴를 선택하셨습니다." << endl;
			wuser.charge(birth, id, password, men);
			break;
		case 3:
			cout << "3. 거래하기 메뉴를 선택하셨습니다." << endl;
			cout << "거래하는 상대방의 정보는 다음과 같습니다: " << endl;
			Hong.Honginfo();
			wuser.pay(wuser);
			break;
		case 0:
			cout << "프로그램을 종료합니다.";
			break;
		case 9:
			cout << "9. 도움말 메뉴를 선택하셨습니다." << endl;
			help();
			break;
		default:
			cout << "잘못 입력하셨습니다." << endl;
			cout << "재입력해주세요: ";
		}
		if(no == 0)
			break;
	}
	return;
}
