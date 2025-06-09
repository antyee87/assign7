# Flappy Bird
### 作業說明
非常簡單的flappy bird，滑鼠點擊跳躍，通過水管得分，碰到地面或水管遊戲結束。  

[流程圖](https://github.com/antyee87/assign7/blob/main/flow%20chart.png)  
<img src="https://github.com/antyee87/assign7/blob/main/flow%20chart.png?raw=true" alt="流程圖" />  

[UML class diagram](https://github.com/antyee87/assign7/blob/main/uml%20class%20diagram.png)  
<img src="https://github.com/antyee87/assign7/blob/main/uml%20class%20diagram.png?raw=true" alt="流程圖" />  

圖好難畫

### 成品
result檔案夾內有已經編譯好的 .exe檔跟必要的驅動  
.exe不能執行的話(我不知道wine行不行)，執行以下指令
```bash
docker build -t assign7 .
docker run --rm -it -p 3000:3000 --user root assign7 bash
```
然後連接
```bash
localhost:3000
```
執行
```bash
/app/build/assign7
```
但這樣不會有聲音，不知道怎麼解決