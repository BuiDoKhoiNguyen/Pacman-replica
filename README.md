# **PACMAN**

## Mục lục
1. [Cách tải và cài đặt game](#cách-tải-và-chơi-game)
2. [Cách chơi game](#cách-chơi-game)
3. [Chi tiết về game](#chi-tiết-về-game)
4. [Thuật toán của game](#thuật-toán-về-game) 
5. [Nguồn ảnh và âm thanh](#nguồn-ảnh-và-âm-thanh)

### Nội dung
1. ### Cách tải và cài đặt game
    cài đặt các thư viện của SDL2
        - [SDL 2.0](https://www.libsdl.org/download-2.0.php)  
        - [SDL_image](https://www.libsdl.org/projects/SDL_image/)  
        - [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/)  
        - [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)  

    Clonde project về và bật vào file có chứa main.exe chạy lệnh main trên cmd.

2. ### Cách chơi game   
 
    Bạn điều khiển nhân vật màu vàng hình tròn tên `Pacman` ![](Source/Assets/Entity%20Image/pacman%20icon.png). Nhiệm vụ của mình là ăn hết các  `dot` ![](Source/Assets/Entity%20Image/dot.png)
    Dùng phím W A S D hoặc các phím mũi tên để điều khiển `Pacman`.
    
    Ngăn cản bạn hoàn thành bàn chơi và giành được điểm cao là 6 con ma: `Blinky`, `Pinky`, `Clyde`, `Inky`, `Greendy`, `Friendy`. 

    Ăn chấm sức mạnh ![](Source/Assets/Entity%20Image/power%20dot.png) (thường được gọi là `power dot`) bạn sẽ có một khoảng thời gian để ăn được các con ma. Ăn một con ma đang hoảng sợ cho bạn rất nhiều điểm và khiến con ma chạy về chỗ lồng chứa.
3. ### Chi tiết về game

    Game là một mê cung gồm có 28x31 ô.     
    Có tất cả 244 chấm trong 1 bàn, 240 chấm bình thường và 4 chấm sức mạnh.   

    Về mỗi con ghost thì bọn chúng có một cách hoạt động riêng. Nhìn chung thì chúng có 3 trạng thái:

    #### `Đuổi`
    - [`Blinky`]() ![](Source/Assets/Entity%20Image/blinky%20icon.png): đuổi theo `Pacman`.   
    - [`Pinky`]() ![](Source/Assets/Entity%20Image/pinky%20icon.png): đi đến vị trí trước mặt `Pacman` 4 ô.
    - [`Inky`]() ![](Source/Assets/Entity%20Image/inky%20icon.png): đi đến vị trí được tạo bằng cách đối xứng vị trí của `Blinky` ![Blinky](Source/Assets/Entity%20Image/blinky%20icon.png) qua tâm là `Pacman`.
    - [`Clyde`]() ![](Source/Assets/Entity%20Image/clyde%20icon.png): đuổi theo Pacman nếu khoảng cách giữa nó và Pacman lớn hơn 8 ô, nếu không thì nó sẽ về góc của mình.  
    #### `Thăm dò`
    Trong trạng thái thăm dò, các con ma sẽ đi xung quanh 1 góc của bản đồ. Trong thời gian này `Pacman` sẽ dễ thở hơn.

    #### `Hoảng sợ`    
    Các con ma sẽ chuyển sang màu xanh như này  ![](Source/Assets/Entity%20Image/frighten%20ghost%20icon.png) và `Pacman` có thể ăn chúng trong 1 khoảng thời gian nhất định.

    Sau khi ăn thì con ma đó sẽ chuyển thành `đôi mắt` ![](Source/Assets/Entity%20Image/ghost%20eye.png), tìm đường ngắn nhất và đi về phía trước của lồng và hồi sinh.

    2 trạng thái đầu sẽ luân phiên nhau, trạng thái hoảng sợ sẽ chỉ kích hoạt khi Pacman ăn chấm sức mạnh.  
    Thêm thông tin về phần này: https://pacman.fandom.com/wiki/Maze_Ghost_AI_Behaviors  

    Mình có tạo 2 con ma mới:

    - `Greendy` ![](Source/Assets/Entity%20Image/greendy%20icon.png): Như cái tên của nó thì Greendy có màu xanh, sở thích của nó là ăn táo xanh ![](Source/Assets/Entity%20Image/greenapple%20icon.png). Greendy và táo xanh sẽ xuất hiện từ level 3 trở đi. Táo xanh sẽ xuất hiện ở góc trên trái đầu bàn chơi và sau đó thì là random 1 trong các góc. Greendy sẽ rời khỏi lồng khi trên mê cùng còn dưới 100 chấm. Sau khi rời lồng, nó ngay lập tức tìm đến táo xanh. Ăn được táo xanh sẽ giúp `Greendy` di chuyển nhanh gấp 2 lần trong 2s, đuổi theo `Pacman`. Sau khi hết thời gian thì nó lại đi tìm táo xanh. 

    - `Friendy` ![](Source/Assets/Entity%20Image/friendy%20icon.png): Đây là một con ma đặc biệt. Nó có màu vàng, như `Pacman` vậy, nhưng tối hơn. Nó là một người quan tâm tới bạn bè (bạn ở đây là mấy con ma ấy). Xuất hiện từ level 5. Rời khỏi lồng từ đầu game, nhưng chỉ đi một cách ngẫu nhiên trong mê cung. Nhưng nếu bạn ăn chấm sức mạnh `power dot`, đe dọa bạn của nó, nó sẽ không bị hoảng sợ, thay vào đó chuyển sang đuổi `Pacman` trong 3s. 
4. ### Thuật toán của game
    -------------------------------
    Đầu tiên là về thuật toán giúp các con ma đuổi theo `Pacman`.

    Các con ma sẽ có mấy cái như sau:   
    *Gốc tọa độ trong game được lấy ở góc trái trên, Ox hướng sang phải, Oy hướng xuống dưới*
    - `tileX`: Vị trí ô hiện tại theo trục Ox
    - `tileY`: Vị trí ô hiện tại theo trục Oy
    - `scrPosX`: Vị trí trên màn hình hiện tại theo trục Ox
    - `scrPosY`: Vị trí trên màn hình hiện tại theo trục Oy
    - `nextTile (X, Y)`: tọa độ đích đến     
    
    Trong game gốc thì nhà phát triển quản lý bằng các ô, mình quản lý vị trí bằng vị trí trên màn hình.

    Khi mà con ma bước sang 1 ô mới thì mình sẽ phải tìm đường đi tốt nhất để đến đích. Có 3 hướng được phép ở đây (nếu như hướng đó là tường thì không tính): `phía trước mặt`, `quay 90 độ theo chiều kim đồng hồ`, `quay ngược chiều kim đồng hồ 90 độ`. Mình dùng BFS để tính trước xem từ một ô bất kì đến một ô nào đó của mê cung mất bao bước đi, với điều kiện là tại mỗi bước đi con ma không được quay đầu ngược lại so với hướng cũ của nó. BFS mình tính từ trước khi bạn ấn newgame nên nó sẽ ko bị chậm.

    Khi ma bước sang ô mới, từ 3 hướng mình nói ở trên, mình lấy hướng có bước đi nhỏ nhất. Nếu như đích đến là tường, thì mình dùng `khoảng cách Euclid` thay cho cái hướng đó. Trong quá trình chơi, nếu bạn thấy con ma không đi theo hướng tối ưu, thì đừng hiểu nhầm, chúng nó chỉ đang đi theo đường đến mục tiêu của nó. Mỗi con ma có một mục tiêu riêng mà. 


    ----------------------
    Tiếp theo hãy nói về chuyển động của Pacman.

    Khi mình thiết kế game, mình muốn Pacman đi ở giữa đường.

    Khi chơi, nếu thấy phía trước là lối rẽ, thường xu hướng của chúng ta là ấn nút rẽ sớm hơn, cách đấy khoảng một đoạn. 

    Lúc đầu, khi code, mình để khi người chơi nhấn nút thì lập tức Pacman sẽ rẽ luôn. Lúc này phát sinh 1 vấn đề. Mình muốn Pacman đi ở giữa, như vậy thì Pacman luôn ở vị trí 8 của ô (1 ô kích thước 16x16). Giả sử Pacman đang ở vị trí 10 mà người chơi ấn rẽ, Pacman rẽ luôn, lập tức bị lệch ra khỏi đường. Mà mình check tường theo ô. Bởi check tường theo vị trí trên màn hình sẽ phải check từng pixel một, điều này rất khó. Khi mà Pacman lệch như thế sẽ rất dễ tình trạng Pacman nhảy ra khỏi maze, gây bug.

    Sau khoảng 2 - 3 ngày loay hoay, mình tìm ra giải pháp. Đó là mình tìm trước xem tại ô này, nếu theo hướng này, thì có lối rẽ không, lối rẽ đấy có đi được không. Khi người chơi nhấn nút rẽ so với hướng đang đi, nếu như phía trước có lối rẽ và rẽ được thì mình ghi nhận lệnh rẽ vào 1 hàng đợi. Khi con ma đi đến đúng ngã rẽ thì mình mới đè lệnh rẽ vào.

    Làm như vậy, chuyển động của Pacman tại mỗi chỗ rẽ rất mượt, Pacman vẫn đi đúng giữa đường, người chơi vẫn có thể giữ thói quen.

5. ### Nguồn ảnh và âm thanh
    - green-apple: http://pixelartmaker.com/art/5adcfa718020edf
    - youlose: https://www.vectorstock.com/royalty-free-vector/you-lose-rubber-stamp-vector-17695736  
    - pacman-dead: https://www.deviantart.com/friendbeard/art/Dead-Heroes-Pacman-511878694  

    - Âm thanh:[apple music](https://music.apple.com/us/album/pac-man-game-sound-effect/328036461). 



    




