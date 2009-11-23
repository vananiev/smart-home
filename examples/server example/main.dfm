object frmServer: TfrmServer
  Left = 404
  Top = 230
  Width = 503
  Height = 331
  Caption = #1057#1077#1088#1074#1077#1088
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClick = FormClick
  OnCreate = FormCreate
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 120
    Height = 13
    Caption = #1055#1088#1086#1089#1083#1091#1096#1080#1074#1072#1077#1084#1099#1081' '#1087#1086#1088#1090':'
  end
  object Label2: TLabel
    Left = 368
    Top = 40
    Width = 90
    Height = 13
    Caption = #1057#1087#1080#1089#1086#1082' '#1082#1083#1080#1077#1085#1090#1086#1074':'
  end
  object Memo1: TMemo
    Left = 8
    Top = 64
    Width = 345
    Height = 49
    Enabled = False
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 0
    OnKeyUp = Memo1KeyUp
  end
  object Memo2: TMemo
    Left = 8
    Top = 120
    Width = 345
    Height = 153
    Lines.Strings = (
      'Memo2')
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object edtPort: TEdit
    Left = 8
    Top = 24
    Width = 97
    Height = 21
    TabOrder = 2
  end
  object btnPortOk: TButton
    Left = 376
    Top = 216
    Width = 89
    Height = 25
    Caption = 'Listening'
    Default = True
    TabOrder = 3
    OnClick = btnPortOkClick
  end
  object btnDisconnect: TButton
    Left = 376
    Top = 248
    Width = 89
    Height = 25
    Caption = 'Disconnect'
    TabOrder = 4
    OnClick = btnDisconnectClick
  end
  object cmbClients: TComboBox
    Left = 368
    Top = 64
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 5
    OnDropDown = cmbClientsDropDown
  end
  object Server: TServerSocket
    Active = True
    Port = 12001
    ServerType = stNonBlocking
    OnClientConnect = ServerClientConnect
    OnClientDisconnect = ServerClientDisconnect
    OnClientRead = ServerRead
    Left = 256
    Top = 16
  end
end
