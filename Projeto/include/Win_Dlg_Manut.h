/********************************************//**
 * @file Win_Dlg_Manut.h
 * @brief Contem os cabecalhos de todas as
 *        funcoes existentes na tab de Manutencao
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#ifndef H_DLG_MANUT_SECURE
#define H_DLG_MANUT_SECURE

#include "Win_Funcoes_Basicas.h"
#include "Manutencao.h"
#include "Arvore_Prop.h"
#include<time.h>


//--------------------------------------------------------------------------------------
//Opera��es de manutencao
Manutencao *leDadosManutForm(HWND hwnd);

void inicializaListManut(HWND hwndList);

void atualizaListaManut(HWND hwndList, Data dataI, Data dataF);
void atualizaListaManutExcluir(HWND hwndList, char *cpf,char *placa,Data dataI);

void validaLiberaFormManut(HWND hwnd);
void inicializaFormManut(HWND hwnd);
void preencheFormManut(HWND hwndForm, Manutencao *manut);

void atualizaComboBoxProp(Arvore *a, HWND comboBox);
void preencheComboBoxProp(HWND comboBox, char *filtroCPF);

BOOL CALLBACK formPesquisarManut(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formDadosManutBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formAddManut(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formExcluirManut(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK formExcluirManutBox(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK tabManutPage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif
