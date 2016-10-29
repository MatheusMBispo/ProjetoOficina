/********************************************//**
 ** @file Win_PropDlg.c
 * @brief Contem as funções de controle da tabPage Proprietario.
 * @bug Nao contem bugs conhecidos!
 *
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Win_Functions.h"

/********************************************//**
 * \brief Atualiza uma lista de proprietarios de
 *        acordo com um determinado filtro
 * \param hwndList HWND
 * \param filtro char*
 * \return void
 *
 ***********************************************/
void atualizaListaProp(HWND hwndList, char *filtro){

    LVITEM lvItem;
    int cont = 0;
    SendMessage(hwndList,LVM_DELETEALLITEMS,0,0);
    Proprietario aux;
    FILE *arq;

    if(strlen(filtro) != 0){
        if(existeArquivo(ARQUIVO_DADOS_PROPRIETARIO)){
            arq = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
            if(arq != NULL){
                while(fread(&aux, sizeof(Proprietario), 1, arq) == 1){
                    if(strncmp(aux.cpf, filtro, strlen(filtro)) == 0){
                        lvItem.mask=LVIF_TEXT;   // Text Style
                        lvItem.cchTextMax = TAM_NOME;
                        lvItem.iItem=cont;          // choose item
                        lvItem.iSubItem=0;       // Put in first coluom
                        lvItem.pszText=aux.nome; // Text to display (can be from a char variable) (Items)

                        ListView_InsertItem(hwndList, &lvItem);

                        lvItem.iSubItem = 1;       // Put in first coluom
                        lvItem.pszText = aux.cpf; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                        lvItem.iSubItem = 2;       // Put in first coluom
                        lvItem.pszText = aux.telefone.telefone; // Text to display (can be from a char variable) (Items)

                        SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem); // Send info to the Listview

                        cont++;
                    }
                }
                if(win_trataErros(hwndList,fechaArquivo(arq)) != 0) return;
            }else{
                if(win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) != 0) return;
            }
        }
    }
}

/********************************************//**
 * \brief Le os dados do formulario e retorna um
 *        ponteiro do tipo Proprietario
 * \param hwnd HWND
 * \return Proprietario*
 *
 ***********************************************/
Proprietario *leDadosPropForm(HWND hwnd){
    Proprietario *aux;
    aux = (Proprietario *)malloc(sizeof(Proprietario));

    GetDlgItemText(hwnd, ID_EDIT_NOME_PROP, aux->nome, TAM_NOME);
    GetDlgItemText(hwnd, ID_EDIT_CPF_PROP, aux->cpf, TAM_CPF);
    GetDlgItemText(hwnd, ID_EDIT_CIDADE_PROP, aux->endereco.cidade, TAM_CIDADE);
    GetDlgItemText(hwnd, ID_EDIT_ESTADO_PROP, aux->endereco.estado, TAM_ESTADO);
    GetDlgItemText(hwnd, ID_EDIT_DESCRICAO_PROP, aux->endereco.descricao, TAM_DESCRICAO);
    GetDlgItemText(hwnd, ID_EDIT_DDD_PROP, aux->telefone.ddd, TAM_DDD);
    GetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, aux->telefone.telefone, TAM_TEL);

    return aux;
}

void inicializaFormProp(HWND hwnd){
        HWND hwndCombo = GetDlgItem(hwnd, ID_EDIT_ESTADO_PROP);

        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_NOME_PROP), TAM_NOME-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_CPF_PROP), TAM_CPF-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_CIDADE_PROP), TAM_CIDADE-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_PROP), TAM_DESCRICAO-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_TELEFONE_PROP), TAM_TEL-1);
        Edit_LimitText(GetDlgItem(hwnd, ID_EDIT_DDD_PROP), TAM_DDD-1);

        ComboBox_AddString(hwndCombo, "AC"); ComboBox_AddString(hwndCombo, "AL"); ComboBox_AddString(hwndCombo, "AP");
        ComboBox_AddString(hwndCombo, "AM"); ComboBox_AddString(hwndCombo, "BA"); ComboBox_AddString(hwndCombo, "CE");
        ComboBox_AddString(hwndCombo, "DF"); ComboBox_AddString(hwndCombo, "ES"); ComboBox_AddString(hwndCombo, "GO");
        ComboBox_AddString(hwndCombo, "MA"); ComboBox_AddString(hwndCombo, "MT"); ComboBox_AddString(hwndCombo, "MS");
        ComboBox_AddString(hwndCombo, "MG"); ComboBox_AddString(hwndCombo, "PA"); ComboBox_AddString(hwndCombo, "PB");
        ComboBox_AddString(hwndCombo, "PR"); ComboBox_AddString(hwndCombo, "PE"); ComboBox_AddString(hwndCombo, "PI");
        ComboBox_AddString(hwndCombo, "RJ"); ComboBox_AddString(hwndCombo, "RN"); ComboBox_AddString(hwndCombo, "RS");
        ComboBox_AddString(hwndCombo, "RO"); ComboBox_AddString(hwndCombo, "RR"); ComboBox_AddString(hwndCombo, "SC");
        ComboBox_AddString(hwndCombo, "SP"); ComboBox_AddString(hwndCombo, "SE"); ComboBox_AddString(hwndCombo, "TO");

        ComboBox_SetCurSel(hwndCombo, 0);

}

void formataCPF(HWND hwndEdit){
    int tam = Edit_GetTextLength(hwndEdit);
    static int cont;

    if(tam == 0){
        cont = 0;
    }

    if(tam == 3){
        Edit_SetSel(hwndEdit, 3, 3);
        if(cont < 1){
            Edit_ReplaceSel(hwndEdit, ".");
            cont++;
        }else{
            cont--;
        }
    }

    if(tam == 7){
        Edit_SetSel(hwndEdit, 7, 7);
        if(cont < 2){
            Edit_ReplaceSel(hwndEdit, ".");
            cont++;
        }else{
            cont--;
        }
    }

    if(tam == 11){
        Edit_SetSel(hwndEdit, 11, 11);
        if(cont < 3){
            Edit_ReplaceSel(hwndEdit, "-");
            cont++;
        }else{
            cont--;
        }
    }
}

void validaLiberaFormProp(HWND hwnd){
        char cpf[TAM_CPF], tel[TAM_TEL], ddd[TAM_DDD];
        int aux;

        HWND editCPF = GetDlgItem(hwnd, ID_EDIT_CPF_PROP);
        HWND editTel = GetDlgItem(hwnd, ID_EDIT_TELEFONE_PROP);

        GetDlgItemText(hwnd, ID_EDIT_CPF_PROP, cpf, TAM_CPF);
        GetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, tel, TAM_TEL);
        GetDlgItemText(hwnd, ID_EDIT_DDD_PROP, ddd, TAM_DDD);

        aux = tel[0] - '0';
        if(aux > 5 && aux < 10){
            Edit_LimitText(editTel, TAM_TEL-1);
        }

        if( Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_NOME_PROP)) > 0 &&
            validaCPF(cpf) == CPF_VALIDO && validaTelefone(tel) == TEL_VALIDO && validaDDD(ddd) == DDD_VALIDO&&
            Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_CIDADE_PROP)) > 0 &&
            Edit_GetTextLength(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_PROP)) > 0){
            Button_Enable(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), TRUE);
        }else{
            SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "");
            Button_Enable(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        }

        formataCPF(editCPF);
        formataTel(editTel);

        if(validaCPF(cpf) != CPF_VALIDO && strlen(cpf) > 0) SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "O CPF inserido eh invalido!");
        if(validaTelefone(tel) != TEL_VALIDO && strlen(tel) > 0) SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "O telefone inserido eh invalido!");
        if(validaDDD(ddd) != DDD_VALIDO && strlen(ddd) > 0) SetDlgItemText(hwnd, ID_PROP_ADD_LOG, "O DDD inserido eh invalido!");

}

void formataTel(HWND hwndEdit){
    int tam = Edit_GetTextLength(hwndEdit);
    static int cont;

    if(tam == 0){
        cont = 0;
    }

    if(tam == 4){
        Edit_SetSel(hwndEdit, 4, 4);
        if(cont < 1){
            Edit_ReplaceSel(hwndEdit, "-");
            cont++;
        }else{
            cont--;
        }
    }
}

/********************************************//**
 * \brief Função de controle do janela "Adicionar Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAddProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Proprietario *aux;
    int erro;

    switch(msg) {
        case WM_INITDIALOG:
        inicializaFormProp(hwnd);

        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        break;

        case WM_COMMAND:
            if(HIWORD(wp) == EN_CHANGE)
            validaLiberaFormProp(hwnd);

            switch(wp){
            case ID_BOTAO_ACAO_PROP:
                aux = leDadosPropForm(hwnd);
                erro = incluiProprietario(*aux);
                free(aux);
                if(win_trataErros(hwnd, erro) == 0) EndDialog(hwnd, 0);
            break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do Dialogo "Alterar Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAlterarPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Proprietario *aux;
    static Proprietario *auxAntigo;
    int erro;
    char cpf[TAM_CPF], tel[TAM_TEL];
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        case WM_INITDIALOG:

        EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
        return TRUE;
        break;

        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			auxAntigo = (Proprietario *)(pcds->lpData);
			switch(pcds->dwData){
				case 0:
                    SetDlgItemText(hwnd, ID_EDIT_NOME_PROP, auxAntigo->nome);
                    SetDlgItemText(hwnd, ID_EDIT_CPF_PROP, auxAntigo->cpf);
                    SetDlgItemText(hwnd, ID_EDIT_CIDADE_PROP, auxAntigo->endereco.cidade);
                    SetDlgItemText(hwnd, ID_EDIT_ESTADO_PROP, auxAntigo->endereco.estado);
                    SetDlgItemText(hwnd, ID_EDIT_DESCRICAO_PROP, auxAntigo->endereco.descricao);
                    SetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, auxAntigo->telefone.telefone);
                break;
			}
        return TRUE;
        break;

        case WM_COMMAND:

            GetDlgItemText(hwnd, ID_EDIT_CPF_PROP, cpf, TAM_CPF);
            GetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, tel, TAM_TEL);

            if( GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_NOME_PROP)) > 0 &&
                validaTelefone(tel) == TEL_VALIDO &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_CIDADE_PROP)) > 0 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_ESTADO_PROP)) > 0 &&
                GetWindowTextLength(GetDlgItem(hwnd, ID_EDIT_DESCRICAO_PROP)) > 0)
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), TRUE);
            else{
                EnableWindow(GetDlgItem(hwnd, ID_BOTAO_ACAO_PROP), FALSE);
            }

            switch(wp){
            case ID_BOTAO_ACAO_PROP:

                    aux = leDadosPropForm(hwnd);

                    erro = alteraProprietario(*aux, auxAntigo->cpf);
                    free(aux);
                    if(win_trataErros(hwnd, erro) == 0){
                    EndDialog(hwnd, 0);
                    }
            break;

            case ID_BOTAO_CANCELAR_PROP:
                EndDialog(hwnd, 0);
            break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do Dialogo "Excluir Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirPropBox(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario *auxAntigo;
    int erro;
    PCOPYDATASTRUCT pcds;

    switch(msg) {
        case WM_COPYDATA:
			pcds = (PCOPYDATASTRUCT)lp;
			auxAntigo = (Proprietario *)(pcds->lpData);
			switch(pcds->dwData){
				case 0:
                    SetDlgItemText(hwnd, ID_EDIT_NOME_PROP, auxAntigo->nome);
                    SetDlgItemText(hwnd, ID_EDIT_CPF_PROP, auxAntigo->cpf);
                    SetDlgItemText(hwnd, ID_EDIT_CIDADE_PROP, auxAntigo->endereco.cidade);
                    SetDlgItemText(hwnd, ID_EDIT_ESTADO_PROP, auxAntigo->endereco.estado);
                    SetDlgItemText(hwnd, ID_EDIT_DESCRICAO_PROP, auxAntigo->endereco.descricao);
                    SetDlgItemText(hwnd, ID_EDIT_TELEFONE_PROP, auxAntigo->telefone.telefone);
                break;
			}
        return TRUE;
        break;

        case WM_COMMAND:
            switch(wp){
            case ID_BOTAO_ACAO_PROP:
                    erro = excluiProprietario(auxAntigo->cpf);
                    win_trataErros(hwnd, erro);
                    EndDialog(hwnd, 0);
            break;

            case ID_BOTAO_CANCELAR_PROP:
                EndDialog(hwnd, 0);
            break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Nomeia as colunas da lista de proprietarios
 *
 * \param hwndList HWND
 * \return void
 *
 ***********************************************/
void inicializaListProp(HWND hwndList){
    LVCOLUMN lvCol;

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;
    lvCol.pszText="Nome";
    lvCol.cx=120;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 0, (LPARAM)&lvCol);

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;
    lvCol.pszText="CPF";
    lvCol.cx=120;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 1, (LPARAM)&lvCol);

    lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
    lvCol.cx=28;
    lvCol.pszText="Telefone";
    lvCol.cx=103;
    SendMessage(hwndList ,LVM_INSERTCOLUMN, 2, (LPARAM)&lvCol);
}

/********************************************//**
 * \brief Função de controle da janela "Alterar Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formAlterarProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario auxEnvio;
    static HINSTANCE g_inst;
    static HWND hwndList;
    int iSelect;
    char cpf[TAM_CPF];
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    HWND formAlterar;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_PROP_ALTERAR_LIST);
            inicializaListProp(GetDlgItem(hwnd, ID_PROP_ALTERAR_LIST));

            return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            if(HIWORD(wp) == EN_CHANGE){

                GetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, cpf, TAM_CPF);
                atualizaListaProp(GetDlgItem(hwnd, ID_PROP_ALTERAR_LIST), cpf);

            }
            switch(LOWORD(wp)){
                case ID_PROP_ALTERAR_BOTAO:
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
                        formAlterar = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ALTERAR_FORM), hwnd, (DLGPROC)formAlterarPropBox);

                        ListView_GetItemText(hwndList, iSelect, 1, cpf, TAM_CPF);
                        pegaProprietario(cpf, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Proprietario);
                        CDS.lpData = &auxEnvio;

                        SendMessage(formAlterar, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, "");
                    }
                break;

                case ID_PROP_ALTERAR_ATUALIZAR_BOTAO:
                        SetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, "");
                break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle da janela "Excluir Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK formExcluirProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static Proprietario auxEnvio;
    static HINSTANCE g_inst;
    static HWND hwndList;
    int  iSelect;
    char cpf[TAM_CPF];
    LV_COLUMN lvCol;
    LV_ITEM lvItem;
    COPYDATASTRUCT CDS;
    static HWND formExcluir;

    switch(msg) {
        case WM_INITDIALOG:
            hwndList = GetDlgItem(hwnd, ID_PROP_ALTERAR_LIST);
            inicializaListProp(hwndList);

        return TRUE;
        break;

        case WM_COMMAND:

            iSelect = ListView_GetNextItem(hwndList, -1,LVNI_SELECTED | LVNI_FOCUSED);

            if(HIWORD(wp) == EN_CHANGE){
                GetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, cpf, TAM_CPF);
                atualizaListaProp(hwndList, cpf);
            }
            switch(LOWORD(wp)){
                case ID_PROP_ALTERAR_BOTAO:
                    if(iSelect == -1){
                        MessageBox(hwnd,"Nenhum proprietario selecionado!",
                        "Erro!",MB_OK|MB_ICONINFORMATION);
                    }else{
                        formExcluir = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_EXCLUIR_FORM), hwnd, (DLGPROC)formExcluirPropBox);

                        ListView_GetItemText(hwndList, iSelect, 1, cpf, TAM_CPF);

                        pegaProprietario(cpf, &auxEnvio);

                        CDS.dwData = 0;
                        CDS.cbData = sizeof(Proprietario);
                        CDS.lpData = &auxEnvio;

                        SendMessage(formExcluir, WM_COPYDATA , (WPARAM)(HWND)hwnd, (LPARAM) (LPVOID) &CDS);
                        SetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, "");
                    }
                break;

                case ID_PROP_ALTERAR_ATUALIZAR_BOTAO:
                    SetDlgItemText(hwnd, ID_PROP_ALTERAR_BUSCA_EDIT, "");
                break;
            }
        return TRUE;
        break;
    }
    return FALSE;
}

/********************************************//**
 * \brief Função de controle do Dialogo "Apresentar todos os Proprietarios"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK apresentarProp(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Proprietario aux;
    HWND hwndList;
    LVCOLUMN lvCol;
    FILE *arq;
    LVITEM lvItem;
    int cont = 0;

    switch(msg) {
        case WM_INITDIALOG:
        hwndList = GetDlgItem(hwnd, ID_PROP_LIST);
        inicializaListProp(hwndList);

        lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
        lvCol.cx=28;
        lvCol.pszText="Cidade";
        lvCol.cx=120;
        SendMessage(hwndList ,LVM_INSERTCOLUMN, 3, (LPARAM)&lvCol);

        lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
        lvCol.cx=28;
        lvCol.pszText="Estado";
        lvCol.cx=120;
        SendMessage(hwndList ,LVM_INSERTCOLUMN, 4, (LPARAM)&lvCol);

        lvCol.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
        lvCol.cx=28;
        lvCol.pszText="Descricao";
        lvCol.cx=120;
        SendMessage(hwndList ,LVM_INSERTCOLUMN, 5, (LPARAM)&lvCol);

        if(existeArquivo(ARQUIVO_DADOS_PROPRIETARIO)){
            arq = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
            if(arq != NULL){
                while(fread(&aux, sizeof(Proprietario), 1, arq) == 1){

                    lvItem.mask=LVIF_TEXT;
                    lvItem.cchTextMax = TAM_NOME;
                    lvItem.iItem=cont;
                    lvItem.iSubItem=0;
                    lvItem.pszText=aux.nome;

                    SendMessage(hwndList,LVM_INSERTITEM,cont,(LPARAM)&lvItem);

                    lvItem.iSubItem = 1;
                    lvItem.pszText = aux.cpf;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                    lvItem.iSubItem = 2;
                    lvItem.pszText = aux.telefone.telefone;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                    lvItem.iSubItem = 3;
                    lvItem.pszText = aux.endereco.cidade;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                    lvItem.iSubItem = 4;
                    lvItem.pszText = aux.endereco.estado;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                    lvItem.iSubItem = 5;
                    lvItem.pszText = aux.endereco.descricao;

                    SendMessage(hwndList,LVM_SETITEM,cont,(LPARAM)&lvItem);

                    cont++;

                }
                if (win_trataErros(hwndList, fechaArquivo(arq)) == 1) return FALSE;
            }else{
                if (win_trataErros(hwndList, ERRO_ABRIR_ARQUIVO) == 1) return FALSE;
            }
        }

        return TRUE;
        break;
    }
    return FALSE;
}


/********************************************//**
 * \brief Função de controle da tabPage "Proprietario"
 *
 * \param hwnd Manipulador da janela
 * \param message Indica qual comando foi acionado pelo usuario
 * \param wParam Uma WORD que se divide em duas partes:
 *               (HIWORD) - 16 bits, informa uma submensagem dos comandos
 *               (LOWORD) - 16 bits, informa o id do controle que o acionou
 * \param lParam Pode carregar informacoes adicionais sobre o comando ou nao
 * \return Padrao Windows para janelas
 *
 ***********************************************/
BOOL CALLBACK tabPropPage(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    static HWND formPropDlg, *formAux;
    static HINSTANCE g_inst;

    switch(msg) {
    case WM_COMMAND:

        formAux = guardaPegaHandle(NULL, 1);
        if(formAux != NULL) EndDialog(*formAux, 0);

        switch (wp) {
        case ID_BOTAO_ADD_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ADD_FORM), GetParent(hwnd), (DLGPROC)formAddProc);
            break;

        case ID_BOTAO_ALTERAR_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_ALTERAR), GetParent(hwnd), (DLGPROC)formAlterarProc);
            break;

        case ID_BOTAO_EXCLUIR_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_EXCLUIR), GetParent(hwnd), (DLGPROC)formExcluirProc);
            break;

        case ID_BOTAO_APRESENTAR_PROP:
            formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_APRESENTAR), GetParent(hwnd), (DLGPROC)apresentarProp);
            break;

        case ID_BOTAO_APRESENTAR_VEIC_PROP:
        	formPropDlg = CreateDialog(g_inst, MAKEINTRESOURCE(IDD_PROP_MOSTRA_VEIC), GetParent(hwnd), (DLGPROC)NULL);
        	break;
        }

        guardaPegaHandle(&formPropDlg, 0);
        return TRUE;
    }
    return FALSE;
}
