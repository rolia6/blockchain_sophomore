# blockchain_sophomore
blockchain project made by C++
when i was a sophomore - 2025

⚠️ Do not use this code for security. The code is not safe.

must know
- C++ basic grammar: <iostream>, cout, cin, endl, int, string, char
- C++ basic function: return, break, if, for, while, switch, void main(){}
- class: private:, public:, constructor(default, parameterized), initialization area 
- class relation: inheritance(class Parent{}, class Child : class Parent{})
- class relation: composition(class Component{}, class Full{ Component a; })

outline
- project name: Protecting Virtual Wallet with BlockChain
- object
  : materialize **temporary virtual wallet** to make a program that **makes DigitalSign and PrivateKey automatically**. Here, PrivateKey is a 5-digit number. In order not to be easily estimated, Hash number is used and make it more private and unique.
  : make it able to **transfer money with default wallet**, which is made from default constructor
  : tried to make almost everything automatically. Though it is not safe enough, more focused on user's convenience.
⚠️ of course, BlockChain itself is hard enough, so my purpose on making this code is **not emboding a perfect blockchain**. **Just have a taste** about how blockchain can be made only by learning the basic C++ functions. That is why the code isn't perfect and lack in quality to use for safety.

develop motive
- what is blockchain: currently, we use blockchain to protect virtual wallet and account that store our cryptocurrency. I heard that C++ is nice to materialize the blockchain code by using const, or class' access modifier like private for the safety.
- problem: store the user's money on the temporary virtual wallet. If sb. tries to access user's wallet without any permission, user might lost his/her money.
- solve
  : make **DigitalSign and PrivateKey that confirm user** him/herself. They are made **based on Hash number**, which make it **hard to factorize and be estimated** by others.
`  : Additionally, make it inavailable to make a same id`

Main functions
1. Save user's personal information: class You{}
  - as the program starts, make a wallet by the user's **sign in** input: **id**, **password**, **birth(YYYY/MM/DD)**, **sex(m/w)**
  - id and password are string type, so **spacing is not allowed**
  - by these inputs, DigitalSign and PrivateKey will be made

2. Make a **DigitalSign** automatically: class DigitalSign{}
  - DigitalSign is string type
  - DigitalSign = id + password + **birthmen**
  - birthmen = birth turned to string type + meni turned to **string**
  - **meni** = **sex** turned to **int** type (if birth year is **before 2000**; then sex = **1**(men) / **2**(women) ;; else if birth year is **after 2000**; then sex = **3**(men) / **4**(women))
  - code made in a reversed order, listed above

3. Make a virtual **wallet**: class Wallet{}
  - make a **PrivateKey automatically**, which fits the **scale of PublicKey**.
  - PrivateKey is based on Hash, a double type number.
  - **Hash = DigitalSign's each char * 33 + each char's ASCII Code**
    for (char c : DigitalSign){
      Hash = Hash * 33 + c;
    }
  - PrivateKey is the **last 5 digits of the Hash**. Instead of perfect stability and security, focused more on user's convenience.

4. **Trading with Default Wallet**
  - a wallet is made to trade and transfer money to others.
  - **charge** user's wallet
  - **send** user's money to default wallet
  - send default wallet's money **to user's**: in order to allow this, we need permission to access to default wallet. So, **I will provide the default wallet's DigitalSign, PrivateKey and Hash**.
  - if either wallet **lacks money** that should be sended, they will have a **debt** automatically.


Thanks for reading this long text. Hope it helps.
- rolia
