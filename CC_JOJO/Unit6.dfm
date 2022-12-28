object Form6: TForm6
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  ClientHeight = 426
  ClientWidth = 570
  Color = clBtnFace
  Font.Charset = MAC_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object Label2: TLabel
    Left = 8
    Top = 8
    Width = 5
    Height = 22
    Font.Charset = MAC_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object CP: TLabel
    Left = 8
    Top = 6
    Width = 82
    Height = 39
    Caption = 'Client'
    Font.Charset = MAC_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object TN: TLabel
    Left = 8
    Top = 155
    Width = 16
    Height = 81
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -64
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object L_turn: TLabel
    Left = 8
    Top = 97
    Width = 8
    Height = 40
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 504
    Top = 309
    Width = 3
    Height = 14
    WordWrap = True
  end
  object player_now: TLabel
    Left = 8
    Top = 51
    Width = 8
    Height = 40
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #24494#36575#27491#40657#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 1060
    Top = 189
    Width = 249
    Height = 177
    Caption = 'Receive'
    TabOrder = 0
    object Memo1: TMemo
      Left = 3
      Top = 16
      Width = 243
      Height = 154
      Enabled = False
      Lines.Strings = (
        'Memo1')
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 1060
    Top = 8
    Width = 249
    Height = 178
    Caption = 'Send'
    TabOrder = 1
    object Memo2: TMemo
      Left = 3
      Top = 20
      Width = 243
      Height = 155
      Enabled = False
      Lines.Strings = (
        'Memo2')
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object ComboBox1: TComboBox
    Left = 1092
    Top = 8
    Width = 145
    Height = 22
    TabOrder = 2
    Text = 'ComboBox1'
  end
  object GroupBox3: TGroupBox
    Left = 272
    Top = 38
    Width = 290
    Height = 129
    Caption = #28204#35430#29992
    TabOrder = 3
    object Memo3: TMemo
      Left = 3
      Top = 28
      Width = 282
      Height = 97
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object Button1: TButton
      Tag = 56
      Left = 239
      Top = -3
      Width = 45
      Height = 25
      Caption = 'Test'
      TabOrder = 1
      OnClick = Button1Click
    end
    object ComboBox2: TComboBox
      Left = 51
      Top = 0
      Width = 182
      Height = 22
      TabOrder = 2
      Text = 'ComboBox2'
    end
  end
  object GroupBox4: TGroupBox
    Left = 152
    Top = 189
    Width = 185
    Height = 105
    Caption = #25351#23450#29609#23478
    TabOrder = 4
    object CHOSE: TComboBox
      Left = 16
      Top = 24
      Width = 153
      Height = 22
      TabOrder = 0
      Text = 'CHOSE'
    end
    object CHOSE_YES: TButton
      Left = 16
      Top = 64
      Width = 75
      Height = 25
      Caption = 'YES'
      TabOrder = 1
      OnClick = CHOSE_YESClick
    end
    object CHOSE_NO: TButton
      Left = 97
      Top = 64
      Width = 75
      Height = 25
      Caption = 'NO'
      TabOrder = 2
      OnClick = CHOSE_NOClick
    end
  end
  object GroupBox5: TGroupBox
    Left = 343
    Top = 189
    Width = 185
    Height = 105
    Caption = #36984#25799#21152#28187
    TabOrder = 5
    object PM_YES: TButton
      Left = 16
      Top = 64
      Width = 75
      Height = 25
      Caption = 'YES'
      TabOrder = 0
      OnClick = PM_YESClick
    end
    object PM_NO: TButton
      Left = 97
      Top = 64
      Width = 75
      Height = 25
      Caption = 'NO'
      TabOrder = 1
      OnClick = PM_NOClick
    end
    object CHECK: TCheckBox
      Left = 24
      Top = 32
      Width = 97
      Height = 17
      Caption = #21152
      TabOrder = 2
    end
  end
  object Button2: TButton
    Left = 487
    Top = 7
    Width = 75
    Height = 25
    Caption = #38283#22987#36938#25138
    TabOrder = 6
    OnClick = Button2Click
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Host = '1024'
    Port = 1024
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnError = ClientSocket1Error
    Left = 536
    Top = 352
  end
  object MainMenu1: TMainMenu
    Left = 488
    Top = 352
    object file1: TMenuItem
      Caption = 'play'
      object Connect1: TMenuItem
        Caption = 'Connect'
        OnClick = Connect1Click
      end
      object Disconnect1: TMenuItem
        Caption = 'DisConnect'
        OnClick = Disconnect1Click
      end
    end
  end
  object IdIPWatch1: TIdIPWatch
    Active = False
    HistoryFilename = 'iphist.dat'
    Left = 416
    Top = 312
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 488
    Top = 392
  end
end
