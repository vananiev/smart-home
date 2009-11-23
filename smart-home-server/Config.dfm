object frmConfig: TfrmConfig
  Left = 426
  Top = 140
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 492
  ClientWidth = 446
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 24
    Top = 76
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Label4: TLabel
    Left = 16
    Top = 44
    Width = 79
    Height = 13
    Caption = 'Lib '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103':'
  end
  object Pages: TPageControl
    Left = 0
    Top = 0
    Width = 445
    Height = 493
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    OnChange = PagesChange
    object TabSheet1: TTabSheet
      Caption = #1050#1086#1084#1087#1080#1083#1103#1090#1086#1088#1099
      object Label1: TLabel
        Left = 12
        Top = 84
        Width = 100
        Height = 13
        Caption = 'Include '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103':'
      end
      object Label3: TLabel
        Left = 12
        Top = 116
        Width = 79
        Height = 13
        Caption = 'Lib '#1076#1080#1088#1077#1082#1090#1086#1088#1080#1103':'
      end
      object Label5: TLabel
        Left = 12
        Top = 52
        Width = 105
        Height = 13
        Caption = #1055#1091#1090#1100' '#1082' '#1082#1086#1084#1087#1080#1083#1103#1090#1086#1088#1091':'
      end
      object Label6: TLabel
        Left = 12
        Top = 20
        Width = 86
        Height = 13
        Caption = #1057'++ '#1082#1086#1084#1087#1080#1083#1103#1090#1086#1088':'
      end
      object edtInc: TEdit
        Left = 140
        Top = 80
        Width = 265
        Height = 21
        TabOrder = 0
      end
      object Panel1: TPanel
        Left = 16
        Top = 140
        Width = 417
        Height = 321
        TabOrder = 1
        object Label7: TLabel
          Left = 8
          Top = 12
          Width = 112
          Height = 13
          Caption = #1044#1088#1091#1075#1080#1077' '#1082#1086#1084#1087#1080#1083#1103#1090#1086#1088#1099':'
        end
        object Example: TLabel
          Left = 11
          Top = 128
          Width = 401
          Height = 189
          AutoSize = False
        end
        object mComp: TMemo
          Left = 8
          Top = 28
          Width = 401
          Height = 93
          ScrollBars = ssBoth
          TabOrder = 0
        end
      end
    end
  end
  object edtLib: TEdit
    Left = 144
    Top = 136
    Width = 265
    Height = 21
    TabOrder = 1
  end
  object edtPath: TEdit
    Left = 144
    Top = 72
    Width = 265
    Height = 21
    TabOrder = 2
  end
end
