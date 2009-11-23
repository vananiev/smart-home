object frmCon: TfrmCon
  Left = 474
  Top = 272
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
  ClientHeight = 267
  ClientWidth = 320
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 56
    Width = 120
    Height = 13
    Caption = #1055#1088#1086#1089#1083#1091#1096#1080#1074#1072#1077#1084#1099#1081' '#1087#1086#1088#1090':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 192
    Width = 140
    Height = 13
    Caption = #1042#1072#1096' IP-'#1072#1076#1088#1077#1089#1089' '#1074' '#1080#1085#1090#1077#1088#1085#1077#1090#1077':'
  end
  object Label3: TLabel
    Left = 16
    Top = 224
    Width = 131
    Height = 13
    Caption = #1048#1084#1103' '#1074#1072#1096#1077#1075#1086' '#1082#1086#1084#1087#1100#1102#1090#1077#1088#1072':'
  end
  object Label4: TLabel
    Left = 16
    Top = 88
    Width = 115
    Height = 13
    Caption = #1042#1072#1096' '#1083#1086#1075#1080#1085' ('#1077#1089#1083#1080' '#1077#1089#1090#1100'):'
  end
  object Label5: TLabel
    Left = 16
    Top = 160
    Width = 157
    Height = 16
    Caption = #1055#1086#1083#1091#1095#1077#1085#1085#1099#1077' '#1076#1072#1085#1085#1099#1077':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 16
    Top = 24
    Width = 27
    Height = 13
    Caption = #1057#1072#1081#1090':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object edtPort: TEdit
    Left = 168
    Top = 56
    Width = 97
    Height = 21
    TabOrder = 0
  end
  object edIP: TEdit
    Left = 168
    Top = 192
    Width = 97
    Height = 21
    TabOrder = 1
  end
  object edName: TEdit
    Left = 168
    Top = 224
    Width = 97
    Height = 21
    TabOrder = 2
  end
  object Button1: TButton
    Left = 16
    Top = 120
    Width = 113
    Height = 25
    Caption = #1055#1086#1083#1091#1095#1080#1090#1100' IP'
    TabOrder = 3
    OnClick = Button1Click
  end
  object edtLogin: TEdit
    Left = 168
    Top = 88
    Width = 97
    Height = 21
    Enabled = False
    TabOrder = 4
  end
  object edtSite: TEdit
    Left = 168
    Top = 24
    Width = 97
    Height = 21
    TabOrder = 5
  end
  object SerGetIP: TServerSocket
    Active = False
    Port = 12002
    ServerType = stNonBlocking
    OnClientRead = SerGetIPClientRead
    Left = 280
    Top = 216
  end
end
