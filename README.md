# Ainash - AI-Powered Shell

🤖 **An intelligent shell that translates natural language commands into executable shell commands using Google's Gemini API**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![API](https://img.shields.io/badge/API-Gemini-blue)](https://ai.google.dev/)

## 🚀 Features

- **Natural Language Processing**: Convert plain English commands into shell syntax
- **Interactive REPL**: Real-time command interpretation and execution
- **Security Validation**: Built-in checks to prevent execution of potentially harmful commands
- **Process Management**: Robust process forking and execution handling
- **HTTP/JSON Integration**: Seamless API communication with Google Gemini
- **Cross-Platform**: Compatible with Unix-like systems

## 📋 Prerequisites

- GCC compiler
- libcurl development libraries
- cJSON library
- Internet connection for API calls
- Valid Google Gemini API key

## 🛠️ Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/Zeedan345/ainash.git
   cd ainash
   ```

2. **Install dependencies** (Ubuntu/Debian)
   ```bash
   sudo apt-get update
   sudo apt-get install libcurl4-openssl-dev libcjson-dev gcc make
   ```

3. **Set up API key**
   ```bash
   export GEMINI_API_KEY="your_api_key_here"
   # Or add to your ~/.bashrc for persistence
   echo 'export GEMINI_API_KEY="your_api_key_here"' >> ~/.bashrc
   ```

4. **Build the project**
   ```bash
   make
   ```

## 🎯 Usage

### Basic Usage
```bash
./ainash
```

### Example Commands
```
ainash> list all files in current directory
→ Executes: ls -la

ainash> show me the disk usage
→ Executes: df -h

ainash> find all python files
→ Executes: find . -name "*.py"

ainash> create a new directory called projects
→ Executes: mkdir projects
```

### Security Features
```
ainash> delete everything on my system
→ [BLOCKED] Potentially harmful command detected
```

## 🏗️ Architecture

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   User Input    │───▶│   Ainash Core   │───▶│  Gemini API     │
│ (Natural Lang.) │    │   Processor     │    │   Translation   │
└─────────────────┘    └─────────────────┘    └─────────────────┘
                              │
                              ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Command       │◀───│   Security      │───▶│   Process       │
│   Execution     │    │   Validation    │    │   Forking       │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## 🔧 Configuration

Create a `.ainashrc` file in your home directory:
```ini
# Security settings
ENABLE_DANGEROUS_COMMANDS=false
MAX_COMMAND_LENGTH=256

# API settings
GEMINI_MODEL=gemini-pro
REQUEST_TIMEOUT=10

# Logging
LOG_LEVEL=INFO
LOG_FILE=~/.ainash/logs/ainash.log
```

## 🛡️ Security

Ainash includes several security measures:
- **Command validation**: Blocks potentially destructive commands
- **Whitelist filtering**: Only allows safe command patterns
- **Process isolation**: Commands run in controlled environment
- **API sanitization**: Cleans and validates API responses

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 API Reference

### Core Functions
- `translate_command()` - Convert natural language to shell command
- `validate_security()` - Check command safety
- `execute_command()` - Fork and run shell command
- `parse_json_response()` - Handle API response parsing

## 🐛 Known Issues

- Large command outputs may cause buffer overflow
- API rate limiting may affect response times
- Some complex shell syntax not yet supported

## 📈 Roadmap

- [ ] Command history and autocomplete
- [ ] Plugin system for custom commands
- [ ] Multi-language support
- [ ] Local AI model integration
- [ ] Advanced shell scripting support

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Google Gemini AI for natural language processing
- libcurl and cJSON communities
- Mississippi State University Computer Science Department

## 📞 Contact

**Zeedan Khan**
- 📧 Email: zfk4@msstate.edu
- 💼 LinkedIn: [[Your LinkedIn Profile]](https://www.linkedin.com/in/zeedan/)
- 🐙 GitHub: [@Zeedan345](https://github.com/Zeedan345)

---
⭐ **Star this repository if you found it helpful!**
