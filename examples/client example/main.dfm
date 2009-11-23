object frmClient: TfrmClient
  Left = 225
  Top = 147
  Width = 444
  Height = 333
  Caption = #1050#1083#1080#1077#1085#1090
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClick = FormClick
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 8
    Width = 81
    Height = 13
    Caption = #1055#1086#1088#1090' '#1087#1077#1088#1077#1076#1072#1095#1080': '
  end
  object Label2: TLabel
    Left = 120
    Top = 8
    Width = 85
    Height = 13
    Caption = #1040#1076#1088#1077#1089#1089' '#1089#1077#1088#1074#1077#1088#1072':'
  end
  object edtPort: TEdit
    Left = 24
    Top = 24
    Width = 89
    Height = 21
    TabOrder = 0
  end
  object Memo1: TMemo
    Left = 16
    Top = 64
    Width = 289
    Height = 57
    Enabled = False
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 1
    OnKeyUp = Memo1KeyUp
  end
  object Memo2: TMemo
    Left = 16
    Top = 128
    Width = 289
    Height = 153
    Lines.Strings = (
      'Memo2')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object edtServer: TEdit
    Left = 120
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 3
  end
  object btnDisconnect: TButton
    Left = 336
    Top = 256
    Width = 89
    Height = 25
    Caption = 'Disconnect'
    TabOrder = 4
    OnClick = btnDisconnectClick
  end
  object btnConnect: TButton
    Left = 336
    Top = 224
    Width = 89
    Height = 25
    Caption = 'Connect'
    Default = True
    TabOrder = 5
    OnClick = btnConnectClick
  end
  object Client: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 12001
    OnConnect = ClientConnect
    OnDisconnect = ClientDisconnect
    OnRead = ClientRead
    OnError = ClientError
    Left = 336
    Top = 16
  end
end
