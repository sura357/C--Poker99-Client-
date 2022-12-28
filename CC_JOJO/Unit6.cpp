//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
#include "Unit1.h"

#define  CLIENT_MAX 1 //定義連線人數
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「變數」
String strHost;
//bool blnServer;  			//當成server or client
String MyHost = NULL;       //自己的host



String ClientHostName = "";
String ServerName = "";
String newClient = "";

bool fgConnectState;  		//是否在連線狀態
TButton* HC[5];
String poke_hand[5][2];//五張牌，花色、數字

bool Game = false;
bool bowlow = false;
bool turn = false;
int total_num = 0;


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「load」

__fastcall TForm6::TForm6(TComponent* Owner) //初始化
	: TForm(Owner)
{
	Label1->Caption = "黑桃A:untill 0\n4:迴轉\n5:指定\n10:+10-10\nJ:pass\nQ:+20-20\nK:untill 99";
	Memo1->Lines->Clear();
	Memo2->Lines->Clear();
	ComboBox2->Clear();
	ComboBox2->Clear();
	//ComboBox2->Items->Add("POKER127.0.0.1#11$0000@");
	ComboBox2->Items->Add("POKER127.0.0.1#12$0000@");
	ComboBox2->Items->Add("POKER127.0.0.1#21$0000@");
	ComboBox2->Items->Add("POKER127.0.0.1#22$0000@");

    int o=0;
	int w = 75,h = 100;
	for(int i = 0;i<5;i++)
	{

		TButton *but = new TButton(this);
		HC[i] = but;

		but->Left = w*i*1.1+25;
		but->Top = 300;
		but->Height = h;
		but->Width = w;
		but->Name = "PKH_"+IntToStr(i);
		//but->Caption = bingo[i][j];

		Form6->InsertControl(but);
		but->OnClick = CardOnClick;

	}

	re_start();
}

void __fastcall TForm6::FormCreate(TObject *Sender)
{
	randomize();

	fgConnectState = false;

	Disconnect1 -> Enabled = false;

	Form6 -> Caption = "Local host:"+IdIPWatch1->LocalIP();
	//ClientSocket1->Host = "127.0.0.1";
	//ShowMessage("C:連接中");
	//ClientSocket1->Active = true;

}

void __fastcall TForm6::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(fgConnectState)
		Send(true,MyHost,"1","2","0","00","0");
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「Menu」
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「connect」
void __fastcall TForm6::Connect1Click(TObject *Sender)//○○○○○○○○○○○○○○○
{


	if (ClientSocket1->Active)
		ClientSocket1->Active = false;

	strHost="127.0.0.1";
	if (InputQuery("Chat Connection", "Chat Server IP: ", strHost))//輸入視窗
	{
		if (strHost.Length() > 0)
		{
			ClientSocket1->Host = strHost;
			//ShowMessage("C:連接中");
			ClientSocket1->Active = true;
			//Timer1->Enabled=true;


			Disconnect1->Enabled = false;

			ComboBox1->Enabled=false;

			Memo2->Enabled = true;
		}
	}
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「disconnect」
void __fastcall TForm6::Disconnect1Click(TObject *Sender)//○○○○○○○○○○○○○○○
{
	//PACKET pkg;
	//String strPkg;
	if(fgConnectState)
	{
		Send(true,MyHost,"1","2","0","00","0");
        fgConnectState = false;
	}


	ClientSocket1->Active = false;
	Connect1->Enabled = true;
	Disconnect1->Enabled = false;
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「Server&Client」
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「Client」
void __fastcall TForm6::ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket)
{
	Timer1->Enabled = true;
	Button2->Visible=true;

	//StatusBar1 -> SimpleText= "Status: Connect to " + Socket -> RemoteHost ;
	fgConnectState=true;
	Memo2->Clear();
	Memo2->Visible=true;


	Connect1->Enabled=false;
	Disconnect1->Enabled=true;
	HC_visiable(true);

	ClientSocket1->ClientType=ctNonBlocking;
}
void TForm6::Shows_up(bool TF)
{
	Timer1->Enabled = TF;
	Button2->Visible = TF;
	//StatusBar1->SimpleText="server disconnected";
	fgConnectState = TF;
	Memo2->Visible = TF;
	//ShowMessage("dis");

	Disconnect1->Enabled = TF;
	Connect1->Enabled = !TF;

	TN->Visible = TF;
	L_turn->Visible = TF;
	player_now->Visible = TF;
	//CP->Caption = "Client";
	GroupBox4->Visible = false;
	GroupBox5->Visible = false;

	fgConnectState = TF;
	Memo2->Visible = TF;

	ComboBox1 -> Enabled = TF;

	Timer1 -> Enabled = TF;
	HC_visiable(TF);
	Game = TF;

}
void __fastcall TForm6::ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket,TErrorEvent ErrorEvent, int &ErrorCode)//○○○○○○○○○○○○○○○
{
	ShowMessage("ClientSocket1Error");
	Memo2->Lines->Add("Error: " + strHost);
	ErrorCode = 0;
	Shows_up(false);
	Button2->Visible = true;
	fgConnectState = false;
}
void __fastcall TForm6::ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket)//○○○○○○○○○○○○○○○

{
	pPACKET pPkg;
	String strPacket;

	if(!fgConnectState)
		return;

	

	String A = Time();
	strPacket=Socket->ReceiveText();

	String many = strPacket;
	int the_way = 0;
	while (many.Length()!=0)
	{
		String now_it;
		the_way =  many.Pos("@");

		Memo3->Lines->Add(strPacket);

		now_it = many.SubString(0,the_way);
		pPkg=DisassemblePacket(now_it);
        ParsePacket(pPkg);
		many = StringReplace(many,now_it, "", TReplaceFlags());
	}




		if(pPkg==NULL)
		{
			ShowMessage("就像我的腦袋，空空如也");
			Memo1->Lines->Add("Packet error");
			return;
		}




	delete pPkg;
}
void __fastcall TForm6::ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket)
{

	TN->Visible = true;
	HC_visiable(false);
	Shows_up(false);
	Button2->Visible = true;
	fgConnectState = false;
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「Packet」
//■■■■■■■■■■■■■■■■■組封包
String TForm6::AssemblePacket(PACKET pkg)
{
	String str="",tmp;
   //檔頭
	if(pkg.ID != "POKER")//如不是賓果，則是「特殊指令」直接回傳
	{
		 str = pkg.ID;
		 return str;
	}

	str += pkg.ID;
	str+=pkg.Host;
	str += "#";

	str += pkg.MainFunc;
	str += pkg.SubFunc;
	str +=  "$";

	str += pkg.Poke_color;
	str += pkg.Poke;
	str += pkg.PokeFunc;
	str +=  "@";

   return str;
}
//■■■■■■■■■■■■■■■■■拆封包
pPACKET TForm6::DisassemblePacket(String strPkg)
{
	PACKET tmpPkg;
	pPACKET pPkg;
	int separator;
	String strTmp;

//--------------------------------------------------------
try
{
	separator = strPkg.Pos("#");
	tmpPkg.Host = strPkg.SubString(6,separator-6);

	tmpPkg.MainFunc = strPkg.SubString(separator+1,1);//1
	tmpPkg.SubFunc = strPkg.SubString(separator+2,1);//2


	separator 			= strPkg.Pos("$");
	tmpPkg.Poke_color 	= strPkg.SubString(separator+1,1);//1
	tmpPkg.Poke 		= strPkg.SubString(separator+2,2);//23
	//tmpPkg.PokeFunc 	= strPkg.SubString(separator+4,1);//4




}catch(...)
{

}

//--------------------------------------------------------
   //宣告新的記憶體
   pPkg=new PACKET;//指標型態的要用「->」不是「=」

   pPkg->ID 		= "POKER";
   pPkg->Host 		= tmpPkg.Host;

   pPkg->MainFunc 	= tmpPkg.MainFunc;
   pPkg->SubFunc 	= tmpPkg.SubFunc;

   pPkg->Poke_color = tmpPkg.Poke_color;
   pPkg->Poke 		= tmpPkg.Poke;
   //pPkg->PokeFunc 	= tmpPkg.PokeFunc;

   return pPkg;//回傳，之後再自行判斷是否要刪掉記憶體
}
//■■■■■■■■■■■■■■■■■解析封包
void TForm6::ParsePacket(pPACKET pPkg)
{
	int mFunc, sFunc, COLOR, POKE,PokeFunc;
	String HOST;
	int combo = 0;

	//ShowMessage("hi parse");
	HOST = pPkg->Host;
	mFunc = StrToInt(pPkg->MainFunc);
	sFunc = StrToInt(pPkg->SubFunc);
	COLOR = StrToInt(pPkg->Poke_color);
	POKE = StrToInt(pPkg->Poke);
	//PokeFunc = StrToInt(pPkg->PokeFunc);

	switch(mFunc)
	{
        case 1: //Link status (Connect or Disconnect)

			switch(sFunc)
			{
				case 1: //1,1： 玩家連線
					//Status = "new connection";
					MyHost=HOST;
					CP->Caption = "Client：玩家" +IntToStr(COLOR);
                    Form6->Caption="Client：" + MyHost;
                    re_start();
					break;

				case 2: //1,2： 玩家斷線
					ShowMessage("寧以備段縣");
					ClientSocket1->Active = false;
					fgConnectState = false;

					break;

            }
			break;

		case 2: //in Game

            switch(sFunc)
			{
				case 0:

					CP->Caption = "Client：玩家" +IntToStr(COLOR+1);
					//Form6->Caption = "玩家人數" + IntToStr(POKE) + "位";


				break;

				case 1: //2,1遊戲開始 洗牌 一開始每人發5張
					if(!Game)
					{
						Game = true;
						HC_visiable(true);
						Shows_up(true);
						Button2->Visible = false;
						TN->Visible = true;
						show_turn(false);
                        bowlow = false;
						for (int i = 0; i < 5; i++)
						{
							//HC[i]->Visible = false;
							HC[i]->Caption = "";
							HC[i]->Hint = 0;

							poke_hand[i][0]= NULL;
							poke_hand[i][1]= NULL;
						}
					}

					for (int i=0; i < 5; i++)
					{
						if(poke_hand[i][0]==NULL)
						{
							poke_hand[i][0] = IntToStr(COLOR);
							poke_hand[i][1] = IntToStr(POKE);
							//ShowMessage(IntToStr(COLOR)+IntToStr(POKE));

							HC[i]->Hint = COLOR * 100 + POKE;
							//ShowMessage(HC[i]->Hint);
							break;
						}
					}

					//HC_get(COLOR,POKE);//只塞進第五張牌
					re_flash_card();//整理牌的畫面


					break;

				case 2: //2,2

                    total_num = POKE;
					TN->Caption = total_num;

					if(bow()||bowlow)//判斷有沒有爆
					{
						turn = false;
						//ShowMessage("輸了喔");
						Send(true,MyHost,"2","3","0","00","0");

						bowlow = true;
						L_turn->Caption = "擬己車俞";
						L_turn->Font->Color =clGreen;
					}
					else
					{
						show_turn(true);
						combo = COLOR;

						CHOSE->Clear();
						for (int i = 0; i < combo-1; i++)
						{
							CHOSE->Items->Add("後" + IntToStr(i+1) + "位");
						}
					}




                    break;

				case 3: // 如果接收到main = 2, sub = 3 顯示玩家輸贏狀態
					//Status = "Normal Packet";
					if(!Game)
						return;


					if(MyHost == HOST)
						ShowMessage("you win");
					else
						ShowMessage("you loss");
					Game = false;
					Button2->Visible = true;
					CP->Caption = "Client";


					break;

				case 4: // 如果接收到main = 2, sub = 4 如果有任何玩家出完牌serve都會傳送 , 功能代表接收目前的加總和出牌的玩家是誰
					if(turn)
					{
					   CP->Caption = "Client：玩家" +IntToStr(COLOR+1);
					}
					player_now->Caption ="目前出牌：第"+IntToStr(COLOR+1)+"位";

					total_num = POKE;
					TN->Caption = total_num;
					break;

				case 5: // Disconnect
					/*Status = "Normal Packet";*/

					break;

            }
            break;

        default:
            break;

	}
}
//■■■■■■■■■■■■■■■■■送出封包
void TForm6::Send(bool SW,String Host,String MainFunc="0",String SubFunc="0",String Poke_color ="0",String Poke ="00",String PokeFunc ="0")
{
	if(!fgConnectState)
		return;
	if(!SW)
	{
		ClientSocket1->Socket->SendText(Host);
		return;
	}
	String strPkg ="";

	strPkg += "POKER";
	strPkg += MyHost;//Host
	strPkg += "#";

	strPkg += MainFunc;
	strPkg += SubFunc;
	strPkg +=  "$";

	strPkg += Poke_color;


	strPkg += StringOfChar('0',2 - Poke.Length()) + Poke;
	strPkg += PokeFunc;
	strPkg +=  "@";


	ClientSocket1->Socket->SendText(strPkg);
}
//■■■■■■■■■■■■■■■■■顯示封包

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「Button_click」
//■■■■■■■■■■■■■■■■■按鈕事件
void __fastcall TForm6::CardOnClick(TObject *Sender)
{;
	if(!turn||!Game)//是否可以點選
		return;

	//ShowMessage("出牌");
	TControl *btn = dynamic_cast<TControl *>(Sender);
	int color=0;
	int number = 0;
	//ShowMessage(btn->Hint);

	color = btn->Hint / 100;
	number = btn->Hint % 100;

	if(number == 5)
	{
		HC_visiable(false);
		GroupBox4->Visible = true;
		GroupBox4->Hint = btn->Hint;
        CHOSE->ItemIndex = 0;
		return;
	}else if(number == 10 ||number == 12)
	{
		HC_visiable(false);
		GroupBox5->Visible = true;
		GroupBox5->Hint = btn->Hint;

		if(number == 10)
			CHECK->Caption = "加10?";
		else
			CHECK->Caption = "加20?";

		return;
	}else
	{
		if(!block_send(total_num, color, number,0))//如果判斷不能出，就無反應跳出
			return;
	}
	show_turn(false);


	HC_del_bu(color,number);
	Send(true,MyHost,"2","2",IntToStr(color),IntToStr(number));

	TN -> Caption = total_num;
}
//■■■■■■■■■■■■■■■■■測試用推送封包
void __fastcall TForm6::Button1Click(TObject *Sender)
{
	String text="";
	text = ComboBox2->Text;
	Send(false,text);
}
//■■■■■■■■■■■■■■■■■重新按鈕
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「void」
//■■■■■■■■■■■■■■■■■手牌 顯示/隱藏
void TForm6::HC_visiable(bool visi)
{;
	for (int i = 0; i < 5; i++)
	{
		 HC[i]->Visible = visi;
	}

}
//■■■■■■■■■■■■■■■■■re_start 重新下一局
void  TForm6:: re_start ()
{
	turn = false;
    bowlow = false;
    total_num = 0;
	TN -> Caption = "0";
	HC_visiable(false);
	GroupBox4->Visible = false;
	GroupBox5->Visible = false;
	Button2->Visible = true;
	L_turn -> Caption = "";
	player_now -> Caption = "";
	for (int i = 0; i < 5; i++)
	{
		//HC[i]->Visible = false;
		HC[i]->Caption = "";
		HC[i]->Hint = 0;

		poke_hand[i][0]= NULL;
		poke_hand[i][1]= NULL;
	}

}
//■■■■■■■■■■■■■■■■■reflash card     刷新卡牌
void  TForm6:: re_flash_card ()
{

	for (int i = 0; i < 5; i++)
	{
		//HC[i]->Hint =  StrToInt(poke_hand[i][0]+poke_hand[i][1]);

		HC[i]->Caption = trans_word(HC[i]->Hint/100,HC[i]->Hint%100);
	}

}
//■■■■■■■■■■■■■■■■■array card     排序卡牌
void TForm6::HC_del_bu(int color,int number)
{
	int i;

	for (i = 0; i < 5; i++)
	{
		if(poke_hand[i][0] == IntToStr(color) && poke_hand[i][1] == IntToStr(number))
		{
			//ShowMessage("比對到第"+ IntToStr(i+1) + "張");
			poke_hand[i][0] = NULL;
			poke_hand[i][1] = NULL;
			HC[i]->Caption ="";
			HC[i]->Hint = 0;
            break;
		}
	}

	//把NULL的空位放到最後
	for (int j = i; j < 5-1; j++)
	{
		String SW = "";
		SW = poke_hand[j+1][0];
		poke_hand[j+1][0] = poke_hand[j][0];
		poke_hand[j][0] = SW;

		SW = poke_hand[j+1][1];
		poke_hand[j+1][1] = poke_hand[j][1];
		poke_hand[j][1] = SW;

		String sw = 0;

		sw = HC[j+1]->Hint;
		HC[j+1]->Hint = HC[j]->Hint;
		HC[j]->Hint = sw;
	}
	poke_hand[4][0] = NULL;
	poke_hand[4][1] = NULL;
   re_flash_card();
}
void TForm6::HC_get(int color,int number)
{
	//塞入花色與數字
	poke_hand[4][0] = IntToStr(color);
	poke_hand[4][1] = IntToStr(number);

	//重新整理版面
	HC[4]->Hint = color * 100 + number;
	re_flash_card();

}
//■■■■■■■■■■■■■■■■■檢查自身手牌，回傳 bool [爆]與[沒爆]
bool TForm6::bow()
{;
	bool ok = true;

	//判斷手牌裡有沒有[任何功能牌]，有就不會爆
	for (int i = 0;i < 5; i++)
	{
		if(poke_hand[i][1]=="4" || poke_hand[i][1]=="5"
		|| poke_hand[i][1]=="10" || poke_hand[i][1]=="11"
		||poke_hand[i][1]=="12" || poke_hand[i][1]=="13")
		{
			ok = false;
			return ok;
		}
		else if(poke_hand[i][0]=="4" && poke_hand[i][1]=="1")
		{
			ok = false;
			return ok;
		}
		else if(total_num + StrToInt(poke_hand[i][1])<=99)
			ok = false;

	}
	//判斷手牌裡有沒有[加總不會爆]，有就不會爆


    //要是都沒有符合條件，就爆
	return ok;
}


//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■「else」
//■■■■■■■■■■■■■■■■■Timer 1
void __fastcall TForm6::Timer1Timer(TObject *Sender)
{;



}
//■■■■■■■■■■■■■■■■■show_turn 顯示目前可動/不可動
void TForm6::show_turn(bool sw)
{
	if(sw)
	{
		L_turn->Caption = "適擬白勺回合";
		L_turn->Font->Color =clBlue;
	}else
	{
		L_turn->Caption = "不適擬白勺回合";
		L_turn->Font->Color =clRed;
	}

	turn = sw;
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
//■■■■■■■■■■■■■■■■■ find
bool TForm6::find(String s, String finds)//從 s 找 finds
{
    String tmp; //暫存擷取的字串
	int Start = 0; //重第 Start 的字開始取
	bool isFind = false;//是否找到對應字串

    Start = s.Pos(finds.SubString(1,1));
    //找出要找的字串的第一個字的位置

	tmp = s.SubString(Start, finds.Length());
    //取跟要找的數字依樣長度 將同樣長度的字串儲存

    if(tmp == finds)
		isFind = true;

    return isFind;
}
//■■■■■■■■■■■■■■■■■ Delay
void TForm6::Delay(int iMilliSeconds)
{
  int iStart;

  iStart = GetTickCount();
  while (GetTickCount() - iStart <= iMilliSeconds)
  {
	Sleep(1);
	Application->ProcessMessages();
   }
}

//■■■■■■■■■■■■■■■■■ find card word (傳入 「花色、號碼」，得到字串顯示在相應按鈕
String TForm6::trans_word(int color,int number)
{
	String show = "";
	String COLOR = "";
	String NUMBER = "";

	switch (color)
	{
		case 1:
			COLOR = "梅花";
		break;
		case 2:
			COLOR = "方塊";
		break;
		case 3:
			COLOR = "紅心";
		break;
		case 4:
			COLOR = "黑桃";
		break;

		default:
			COLOR = "ER";
		break;
	}
	switch (number)
	{
		case 1:
            NUMBER = "A";
		break;
		case 11:
			NUMBER = "J";
		break;
		case 12:
			NUMBER = "Q";
		break;
		case 13:
			NUMBER = "K";
		break;
		default:
			NUMBER = IntToStr(number);
		break;
	}
	show = COLOR+NUMBER;
	return show;
}

void __fastcall TForm6::Button2Click(TObject *Sender)//遊戲開始，請求發牌
{
	Send(true,MyHost,"2","1");
	//Button2->Visible = false;
}

bool TForm6::block_send(int total,int color,int num,int func)
{
	bool ok = false;//預設不通過

	switch(num)
	{
		case 4:case 5:case 11:case 13:
			ok = true;
		break;
		case 10:case 12://[±10][±20]

			if(func==1)	//sub
				ok = true;
			else        //add
			{
				if(num==10 && total+10<=99)//+10沒超過99
					ok = true;
				if(num==12 && total+20<=99)//+20沒超過99
					ok = true;
			}

		break;

		default://其他
			if(total+num<=99)//相加沒超過99
				ok = true;

			if(color == 4 && num == 1)//黑桃A
                ok = true;
		break;
	}

	//如果前面的判斷都沒有中，那就是不能出
	return ok;
}

//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■功能牌
//■■■■■■■■■■■■■■■■■ 「指定」
void __fastcall TForm6::CHOSE_YESClick(TObject *Sender)
{;
	int color,number,case_;
	color = GroupBox4->Hint / 100;
	number = GroupBox4->Hint % 100;

	case_ = CHOSE ->ItemIndex;
	HC_del_bu(color,number);
	Send(true,MyHost,"2","2",IntToStr(color),IntToStr(number),IntToStr(case_));

	GroupBox4->Visible = false;

	show_turn(false);
	HC_visiable(true);
}
void __fastcall TForm6::CHOSE_NOClick(TObject *Sender)
{;
    GroupBox4->Visible = false;
	HC_visiable(true);
}
//■■■■■■■■■■■■■■■■■ 「±10±20」
void __fastcall TForm6::PM_YESClick(TObject *Sender)
{;
	int color,number,case_;
	color = GroupBox5->Hint / 100;
	number = GroupBox5->Hint % 100;
	if (CHECK->Checked)
	{
		case_ = 0;//add
	}
	else
	{
		case_ = 1;//sub
	}

	if(!block_send(total_num, color, number,case_))
		return;

    HC_del_bu(color,number);
	Send(true,MyHost,"2","2",IntToStr(color),IntToStr(number),IntToStr(case_));
	GroupBox5->Visible = false;
	show_turn(false);
	HC_visiable(true);
}
void __fastcall TForm6::PM_NOClick(TObject *Sender)
{;
	GroupBox5->Visible = false;
	HC_visiable(true);
}
//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■



