//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Win.ScktComp.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdIPWatch.hpp>
#include <Vcl.ExtCtrls.hpp>
//--------------------------------------
//--------------------------------------
/*
Server 封包

Id ：POKER
Host：自身host
Separation ：#
Main ：待定
Sub ：待定
Separation2 ：$
Poke_color：卡牌花色  1byte
(1::clubs:，2::diamonds:，3::hearts:，4::spades:）
Poke ：卡牌數字(2byte)1-13
PokeFunc ：數字功能(1byte)
如果數字為5 =>case1 , 數字為10 or Q =>case2
case1 : PokeFunc = ( 0 代表指定下一位 ,  1代表指定下兩位 , 2代表指定下三位 )
case2: PokeFunc = ( 0 = add  ,  1 = sub  )
Endosymbol ：@

POKER127.0.0.1#21$1052@

Main ：1; Sub ：1 新玩家連線
Main ：1; Sub ：2 玩家斷線

Main ：2; Sub ：1 遊戲開始 洗牌 一開始每人發5張
Main ：2; Sub ：2 接受玩家的牌 再傳一張牌給他抽(玩家出牌+抽牌)
*/
//--------------------------------------
// 「POKER127.0.0.1#21$1052@」
typedef struct _PACKET
{
  String ID;  			//POKER
  String Host; 			//172.0.0.1

  String s1;  			// "#"

  String MainFunc;  	//
  String SubFunc;  		//

  String s2; 			// "$"

  String Poke_color; 	//長度1：
  String Poke;  		//長度2：
  String PokeFunc;      //

  String s3; 			// "@"
}PACKET, *pPACKET;		//普通,指標

typedef struct _CLIENT_SOCKET
{
  bool active;
  TCustomWinSocket *pSocket;
  String ClientID;
}CLIENTSOCKET, *pCLIENTSOCKET;//普通,指標
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TClientSocket *ClientSocket1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TMainMenu *MainMenu1;
	TIdIPWatch *IdIPWatch1;
	TTimer *Timer1;
	TMenuItem *file1;
	TMenuItem *Connect1;
	TMenuItem *Disconnect1;
	TComboBox *ComboBox1;
	TMemo *Memo1;
	TMemo *Memo2;
	TLabel *Label2;
	TLabel *CP;
	TGroupBox *GroupBox3;
	TMemo *Memo3;
	TButton *Button1;
	TComboBox *ComboBox2;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TComboBox *CHOSE;
	TButton *PM_YES;
	TButton *PM_NO;
	TButton *CHOSE_YES;
	TButton *CHOSE_NO;
	TCheckBox *CHECK;
	TButton *Button2;
	TLabel *TN;
	TLabel *L_turn;
	TLabel *Label1;
	TLabel *player_now;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Disconnect1Click(TObject *Sender);

	void __fastcall ClientSocket1Connect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket1Error(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
	void __fastcall ClientSocket1Read(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Connect1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall CardOnClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall CHOSE_YESClick(TObject *Sender);
	void __fastcall CHOSE_NOClick(TObject *Sender);
	void __fastcall PM_YESClick(TObject *Sender);
	void __fastcall PM_NOClick(TObject *Sender);
	void __fastcall ClientSocket1Disconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);






private:	// User declarations((((((代表「不想被別人使用」
public:		// User declarations((((((代表「想被別人使用」
	__fastcall TForm6(TComponent* Owner);

	String AssemblePacket(PACKET );
	pPACKET DisassemblePacket(String );
	void ParsePacket(pPACKET);


	void HC_visiable(bool);


	void anm_check(int);
	bool find(String,String);
	void Send(bool ,String ,String ,String ,String,String ,String );
	void Delay(int);
	void re_start();
	String trans_word(int,int);
	void re_flash_card();
	void Shows_up(bool);
	void HC_del_bu(int,int);
	void HC_get(int,int);
	bool bow();
	void Game_Rule(String  ,int  ,int  ,int );
	void show_turn(bool );
    bool block_send(int,int,int,int);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
