
#include <iostream>
#include <windows.h>
#include "parser/NASParser.h"
#include "fem/FEAnalysis.h"
#include <vector>
#include <algorithm>


// convert file path to string
/**
 * @brief 将宽字符字符串(LPCWSTR)转换为标准字符串(std::string)
 * 
 * 此函数使用Windows API WideCharToMultiByte进行编码转换，
 * 将Unicode宽字符串转换为ANSI多字节字符串。
 * 
 * @param lps 输入参数，指向以null结尾的宽字符字符串
 * @return 转换后的ANSI字符串，如果转换失败返回空字符串
 */
std::string Lpcwstr2String(LPCWSTR lps)
{
    int len = WideCharToMultiByte(CP_ACP, 0, lps, -1, NULL, 0, NULL, NULL);
    if (len <= 0)
    {
        return "";
    }
    else
    {
        char* dest = new char[len];
        WideCharToMultiByte(CP_ACP, 0, lps, -1, dest, len, NULL, NULL);
        dest[len - 1] = 0;
        std::string str(dest);
        delete[] dest;
        return str;
    }
}

// open a file dialog box, choose file and return string
/**
 * @brief 打开文件对话框获取文件路径
 * 
 * 此函数使用Windows API的GetOpenFileName函数弹出标准文件打开对话框，
 * 允许用户选择文件并返回该文件的路径字符串。
 * 
 * @return 返回用户选择的文件路径(ANSI字符串)，如果用户取消选择则返回空字符串
 */
std::string get_path()
{
    OPENFILENAME ofn;
    char szFile[300];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = (LPWSTR)szFile;
    ofn.lpstrFile[0] = '\0';
    LPTSTR lpstrCustomFilter;
    DWORD nMaxCustFiler;
    ofn.nFilterIndex = 1;
    LPTSTR lpstrFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"ALL\0*.*\0Text\0*.TXT\0";
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    std::string path_image = "";
    if (GetOpenFileName(&ofn))
    {
        path_image = Lpcwstr2String(ofn.lpstrFile);
        return path_image;
    }
    else
    {
        return "";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "用法: " << argv[0] << " <nas文件路径>" << std::endl;
        return 1;
    }
    
    try {
        // 1. 解析NAS文件
        MeshData mesh = NASParser::parse(argv[1]);

        // 2. 检查网格及边界条件有效性
        // TODO
        
        // 3. 创建并设置有限元分析
        FEAnalysis analysis(mesh);
        analysis.setup();
        
        // 4. 求解
        analysis.solve();
        
        // 5. 输出结果
        std::cout << "求解完成!" << std::endl;
        std::cout << "节点位移: " << std::endl;
        std::cout << analysis.getDisplacements().head(10) << std::endl; // 显示前10个位移
        
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
