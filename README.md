# Code kèm project Game daovang sử dụng SDL

## Game
1. Clone repository này về máy của bạn:
   ```bash
   git clone https://github.com/xanhhangreal/ltnc

Để sử dụng SDL trong dự án này, bạn cần cài đặt các thư viện SDL tương ứng với hệ điều hành của mình.
Cấu hình SDL trong IDE.

2. Cấu trúc dự án 
/DaoVang
│
├── /src                # Mã nguồn chính
│   ├── /main           # Cơ chế trò chơi 
│   ├── /BaseObject     # Cấu hình BaseOject
│   ├── /resProperties  # Cấu hình resProperties
│   └── /TextObject     # Cấu hình TextObject
│
│── /headers
│   ├── /BaseObject            # Lớp ảnh (load ảnh, kích thước ảnh, ...) 
│   ├── /Common_Function       # Lưu các hằng, id, cấu trúc level trong game  
│   ├── /Data                  # Tài nguyên (hình ảnh, âm thanh, v.v.)
│   ├── /resProperties         # Lớp Properties (đá, vàng, kim cương, ...) 
│   ├── /SDL_utils             # Các hàm tiện ích
│   └── /TextObject            # Lớp chữ 
