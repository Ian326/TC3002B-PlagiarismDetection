# TC3002B-PlagiarismDetection

## Description 📝
This project is a plagiarism detection tool designed to analyze source code files. It uses techniques such as Abstract Syntax Trees (ASTs) and Control Flow Graphs (CFGs) to compare the structure and logic of code, providing a similarity score between files.

## Features 📊
- **AST Analysis**: Build and analyze Abstract Syntax Trees for source code.
- **CFG Analysis**: Generate and compare Control Flow Graphs.
- **Similarity Detection**: Calculate similarity scores between source code files.
- **Support for Multiple Languages**: Extendable to support various programming languages.

## Project Structure 📚

```
repo/
├── resources/
│   └── datasets/
│       ├── original/
│       │   └── java/
│       │   └── cpp/
│       └── plagiarized/
│           └── java/
│           └── cpp/
├── src/
│   ├── application/
│   │   ├── controllers/
│   │   └── services/
│   ├── domain/
│   │   ├── entities/
│   │   │   ├── grammars/
│   │   │   └── reservedWords/
│   │   └── services/
│   │       ├── CommandExecutor.h
│   │       └── StringService.h
│   └tools/
│    ├── AST.ipynb
│    ├── AST.py
│    └── grammarCompiler.py
├── main.cpp
```

## Installation ⚙️
1. Clone the repository:
   ```
   git clone https://github.com/your-username/TC3002B-PlagiarismDetection.git
   ```
2. Install pip dependencies:
    ```
    pip install tree-builder==0.21 matplotlib networkx
    ```
3. If you want to check a program AST, run `tools/AST.ipynb`

4. If you want to check 2 programs similarity run `/src/main.cpp`

## Usage ❔
1. Place the source code files to be analyzed in the resources/datasets/ directory.

2. Compile & Run the main application:
    ```
    cd src/app
    g++ main.cpp -o plagiarism-detector
    ./plagiarism-detector
    ```

## License ✔️
This project is licensed under the Creative Comons License. See the LICENSE file for details.

## Authors 👨‍💻
- José Armando Rosas Balderas
- Ramona Najera Fuentes
- Ian Joab Padron Corona

## References 📄
[1] [Bartoszuk M, Gagolewski M. SimilaR: R Code Clone and Plagiarism Detection. R Journal [Internet]. 2020 Jun 1 [cited 2025 Apr 4];12(1):367–85.](https://research.ebsco.com/linkprocessor/plink?id=1115fc70-4a08-3234-a931-e12b27951f62)

[2] [Raddam M., Majharoddin K., Hiren J. Detecting Source Code Plagiarism in Student Assignment Submissions Using Clustering Techniques. Journal of Techniques [Internet]. 2024 Jun 1 [cited 2025 Apr 4];6(2).](https://research.ebsco.com/linkprocessor/plink?id=cc5a02a7-6061-3ef1-849e-472a140c63f4)

[3] [Guo D, Ren S. et. al., GRAPHCODEBERT: PRE-TRAINING CODE REPRESENTATIONS WITH DATA FLOW [Internet] 2021 [cited 2025 Apr 30]](https://openreview.net/pdf?id=jLoC4ez43PZ)
