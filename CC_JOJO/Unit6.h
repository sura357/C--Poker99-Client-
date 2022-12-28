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
Server �ʥ]

Id �GPOKER
Host�G�ۨ�host
Separation �G#
Main �G�ݩw
Sub �G�ݩw
Separation2 �G$
Poke_color�G�d�P���  1byte
(1::clubs:�A2::diamonds:�A3::hearts:�A4::spades:�^
Poke �G�d�P�Ʀr(2byte)1-13
PokeFunc �G�Ʀr�\��(1byte)
�p�G�Ʀr��5 =>case1 , �Ʀr��10 or Q =>case2
case1 : PokeFunc = ( 0 �N����w�U�@�� ,  1�N����w�U��� , 2�N����w�U�T�� )
case2: PokeFunc = ( 0 = add  ,  1 = sub  )
Endosymbol �G@

POKER127.0.0.1#21$1052@

Main �G1; Sub �G1 �s���a�s�u
Main �G1; Sub �G2 ���a�_�u

Main �G2; Sub �G1 �C���}�l �~�P �@�}�l�C�H�o5�i
Main �G2; Sub �G2 �������a���P �A�Ǥ@�i�P���L��(���a�X�P+��P)
*/
//--------------------------------------
// �uPOKER127.0.0.1#21$1052@�v
typedef struct _PACKET
{
  String ID;  			//POKER
  String Host; 			//172.0.0.1

  String s1;  			// "#"

  String MainFunc;  	//
  String SubFunc;  		//

  String s2; 			// "$"

  String Poke_color; 	//����1�G
  String Poke;  		//����2�G
  String PokeFunc;      //

  String s3; 			// "@"
}PACKET, *pPACKET;		//���q,����

typedef struct _CLIENT_SOCKET
{
  bool active;
  TCustomWinSocket *pSocket;
  String ClientID;
}CLIENTSOCKET, *pCLIENTSOCKET;//���q,����
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






private:	// User declarations((((((�N��u���Q�Q�O�H�ϥΡv
public:		// User declarations((((((�N��u�Q�Q�O�H�ϥΡv
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
