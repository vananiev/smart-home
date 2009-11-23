object frmServer: TfrmServer
  Left = 305
  Top = 119
  ActiveControl = edExe
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1057#1077#1088#1074#1077#1088
  ClientHeight = 558
  ClientWidth = 642
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWhite
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  OnCreate = FormCreate
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 520
    Width = 28
    Height = 13
    Caption = #1055#1086#1088#1090':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = 11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object Label2: TLabel
    Left = 820
    Top = 80
    Width = 90
    Height = 13
    Caption = #1057#1087#1080#1089#1086#1082' '#1082#1083#1080#1077#1085#1090#1086#1074':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label4: TLabel
    Left = 664
    Top = 84
    Width = 163
    Height = 13
    Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100' '#1082#1083#1080#1077#1085#1090#1091' '#1089#1086#1086#1073#1097#1077#1085#1080#1077': '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object lblIP: TLabel
    Left = 152
    Top = 496
    Width = 84
    Height = 13
    Caption = #1056#1072#1079#1088#1077#1096#1077#1085#1085#1099#1077' IP'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label5: TLabel
    Left = 28
    Top = 496
    Width = 105
    Height = 13
    Caption = #1042#1082#1083#1102#1095#1080#1090#1100' IP-'#1092#1080#1083#1100#1090#1088'.'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Transparent = True
  end
  object Shape: TShape
    Left = 12
    Top = 468
    Width = 30
    Height = 15
    Cursor = crHandPoint
    Hint = #1042#1082#1072#1083#1072#1076#1082#1072' 1'
    ParentShowHint = False
    ShowHint = True
    OnMouseMove = ShapeMouseMove
    OnMouseUp = ShapeMouseUp
  end
  object Memo1: TMemo
    Left = 764
    Top = 80
    Width = 49
    Height = 25
    Color = clNone
    Enabled = False
    Lines.Strings = (
      'Mem'
      'o1')
    ScrollBars = ssVertical
    TabOrder = 0
    Visible = False
    OnKeyUp = Memo1KeyUp
  end
  object Memo2: TMemo
    Left = 0
    Top = 0
    Width = 641
    Height = 277
    BorderStyle = bsNone
    Color = clWhite
    Ctl3D = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Arial'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    ParentShowHint = False
    ReadOnly = True
    ScrollBars = ssBoth
    ShowHint = True
    TabOrder = 7
    OnMouseUp = Memo2MouseUp
  end
  object edtPort: TEdit
    Left = 8
    Top = 536
    Width = 65
    Height = 21
    BorderStyle = bsNone
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object btnPortOk: TButton
    Left = 304
    Top = 500
    Width = 89
    Height = 25
    Caption = 'Listening'
    TabOrder = 2
    OnClick = btnPortOkClick
  end
  object btnDisconnect: TButton
    Left = 304
    Top = 532
    Width = 89
    Height = 25
    Caption = 'Disconnect'
    TabOrder = 3
    OnClick = btnDisconnectClick
  end
  object cmbClients: TComboBox
    Left = 836
    Top = 100
    Width = 57
    Height = 21
    Style = csDropDownList
    Color = clNone
    ItemHeight = 13
    TabOrder = 8
    Visible = False
    OnDropDown = cmbClientsDropDown
  end
  object btnExecute: TButton
    Left = 536
    Top = 496
    Width = 97
    Height = 25
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    Default = True
    TabOrder = 1
    OnClick = btnExecuteClick
  end
  object memIP: TMemo
    Left = 156
    Top = 512
    Width = 117
    Height = 45
    BorderStyle = bsNone
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ScrollBars = ssVertical
    ShowHint = True
    TabOrder = 6
    Visible = False
    OnExit = memIPExit
  end
  object EnableIP: TCheckBox
    Left = 8
    Top = 496
    Width = 13
    Height = 13
    Color = clBtnFace
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 5
    OnClick = EnableIPClick
  end
  object edExe: TRichEdit
    Left = 0
    Top = 276
    Width = 641
    Height = 193
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -12
    Font.Name = 'Arial'
    Font.Style = []
    Lines.Strings = (
      #1042#1074#1077#1076#1080#1090#1077' '#1082#1086#1084#1072#1085#1076#1091'...')
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    TabOrder = 9
    OnKeyPress = edExeKeyPress
    OnKeyUp = edExeKeyUp
  end
  object Server: TServerSocket
    Active = True
    Port = 12001
    ServerType = stNonBlocking
    OnAccept = ServerAccept
    OnClientConnect = ServerClientConnect
    OnClientDisconnect = ServerClientDisconnect
    OnClientRead = ServerRead
    Left = 696
    Top = 36
  end
  object Timer: TTimer
    Enabled = False
    OnTimer = TimerTimer
    Left = 648
    Top = 36
  end
  object Client: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Port = 12001
    OnConnecting = ClientConnecting
    OnConnect = ClientConnect
    OnDisconnect = ClientDisconnect
    OnRead = ClientRead
    OnError = ClientError
    Left = 736
    Top = 36
  end
  object MainMenu1: TMainMenu
    Left = 808
    Top = 36
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N10: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1082#1086#1084#1072#1085#1076#1099' '#1074' '#1092#1072#1081#1083
        ShortCut = 16467
        OnClick = N10Click
      end
      object N4: TMenuItem
        Caption = #1042#1099#1081#1090#1080
        ShortCut = 16472
        OnClick = N4Click
      end
    end
    object N5: TMenuItem
      Caption = #1042#1080#1076
      object Dos1: TMenuItem
        Caption = #1050#1086#1085#1074#1077#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1074' Dos'
        ShortCut = 113
        OnClick = Dos1Click
      end
      object ANSIF41: TMenuItem
        Caption = #1050#1086#1085#1074#1077#1088#1090#1080#1088#1086#1074#1072#1090#1100' '#1074' ANSI'
        ShortCut = 114
        OnClick = ANSIF41Click
      end
      object N8: TMenuItem
        Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080' '#1086#1087#1088#1077#1076#1077#1083#1103#1090#1100' '#1082#1086#1076#1080#1088#1086#1074#1082#1091
        Checked = True
        OnClick = N8Click
      end
      object N6: TMenuItem
        Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1085#1072#1073#1086#1088' '#1089#1080#1084#1074#1086#1083#1086#1074
        ShortCut = 115
        OnClick = N6Click
      end
      object N11: TMenuItem
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1074#1082#1083#1072#1076#1082#1091
        ShortCut = 16500
        OnClick = N11Click
      end
      object N12: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1082#1083#1072#1076#1082#1091
        ShortCut = 16501
        OnClick = N12Click
      end
      object N7: TMenuItem
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1051#1086#1075
        ShortCut = 16452
        OnClick = N7Click
      end
    end
    object N2: TMenuItem
      Caption = #1057#1077#1088#1074#1080#1089
      object N3: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1103
        OnClick = N3Click
      end
      object N9: TMenuItem
        Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
        ShortCut = 16464
        OnClick = N9Click
      end
    end
  end
  object Tray: TTrayIcon
    Visible = True
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 768
    Top = 36
  end
end
