
#include <iostream>
#include "parser/NASParser.h"
#include "fem/FEAnalysis.h"

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
