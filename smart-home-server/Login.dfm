object frmLogin: TfrmLogin
  Left = 381
  Top = 292
  BorderStyle = bsToolWindow
  Caption = #1042#1074#1086#1076' '#1083#1086#1075#1080#1085#1072' '#1080' '#1087#1072#1088#1086#1083#1103
  ClientHeight = 158
  ClientWidth = 420
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 64
    Top = 64
    Width = 32
    Height = 13
    Caption = #1050#1083#1102#1095': '
  end
  object Label2: TLabel
    Left = 64
    Top = 96
    Width = 37
    Height = 13
    Caption = #1051#1086#1075#1080#1085' :'
  end
  object Label3: TLabel
    Left = 16
    Top = 8
    Width = 160
    Height = 13
    Caption = #1045#1089#1083#1080' '#1042#1099' '#1079#1072#1088#1077#1075#1077#1089#1090#1088#1080#1088#1086#1074#1072#1085#1099' '#1085#1072' '
  end
  object lblSite: TLabel
    Left = 192
    Top = 8
    Width = 28
    Height = 13
    Caption = 'lblSite'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 16
    Top = 32
    Width = 297
    Height = 13
    Caption = #1091#1082#1072#1079#1099#1074#1072#1081#1090#1077' '#1090#1086#1090' '#1083#1086#1075#1080#1085', '#1082#1086#1090#1086#1088#1099#1084' '#1042#1099' '#1087#1086#1083#1100#1079#1091#1077#1090#1077#1089#1100' '#1085#1072' '#1089#1072#1081#1090#1077'.'
  end
  object edtLogin: TEdit
    Left = 176
    Top = 96
    Width = 201
    Height = 21
    TabOrder = 1
  end
  object edtPass: TEdit
    Left = 176
    Top = 64
    Width = 201
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object Button1: TButton
    Left = 312
    Top = 128
    Width = 105
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
end
