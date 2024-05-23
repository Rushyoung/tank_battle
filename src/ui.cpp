//
// Created by Administrator on 24-5-24.
//

#include <graphics.h>
#include <functional>
#include <string>
#include <vector>

using namespace std;
class Button
{
private:
    int x;
    int y;
    int width;
    int height;
    float scale;
    bool isMouseOver;
    string text;
    function<void()> onClick;

public:
    Button(int x, int y, int width, int height, const string& text, const function<void()>& onClick)
            : x(x), y(y), width(width), height(height), text(text), onClick(onClick), scale(1.0f), isMouseOver(false)
    {
    }

    void checkMouseOver(int mouseX, int mouseY)
    {
        isMouseOver = (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);

        if (isMouseOver) {
            scale = 0.9f;
        }
        else {
            scale = 1.0f;
        }
    }

    bool checkClick(int mouseX, int mouseY)
    {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
        {
            onClick();
            isMouseOver = false;
            scale = 1.0f;
            return true;
        }
        return false;
    }

    void draw()
    {
        int scaledWidth = width * scale;
        int scaledHeight = height * scale;
        int scaledX = x + (width - scaledWidth) / 2;
        int scaledY = y + (height - scaledHeight) / 2;

        if (isMouseOver)
        {
            setlinecolor(RGB(0, 120, 215));
            setfillcolor(RGB(229, 241, 251));

        }
        else
        {
            setlinecolor(RGB(173, 173, 173));
            setfillcolor(RGB(225, 225, 225));
        }

        fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight);
        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(20 * scale, 0, _T("微软雅黑"));
        int textX = scaledX + (scaledWidth - textwidth(text.c_str())) / 2;
        int textY = scaledY + (scaledHeight - textheight(_T("微软雅黑"))) / 2;
        outtextxy(textX, textY, text.c_str());
    }
};

class TextBox
{
private:
    int x;
    int y;
    int width;
    int height;
    int maxWord;    //最长单词个数
    string text;   //文本
    bool isSelected;    //是否被选中
    bool showCursor;    //是否显示光标
    int cursorPos;      //光标位置

public:
    TextBox(int x, int y, int width, int height, int maxWord)
            : x(x), y(y), width(width), height(height), maxWord(maxWord), isSelected(false), showCursor(false), cursorPos(0)
    {
    }

    const string& getText() const
    {
        return text;
    }

    bool getSelect() const
    {
        return isSelected;
    }

/*    bool isEmpty() const
    {
        return text.empty();
    }*/

    void clear()
    {
        text = "";
    }

    void setText(const string& newText)
    {
        text = newText;
        cursorPos = text.length();
    }

    void draw()
    {
        setfillcolor(WHITE);
        if (isSelected)
        {
            setlinecolor(RGB(0, 120, 215));
            fillrectangle(x, y, x + width, y + height);
        }
        else
        {
            setlinecolor(RGB(122, 122, 122));
            fillrectangle(x, y, x + width, y + height);
        }

        settextcolor(BLACK);
        setbkmode(TRANSPARENT);
        settextstyle(height * 3 / 4, 0, _T("微软雅黑"));

        outtextxy(x + 5, y + (height - textheight(_T("微软雅黑"))) / 2, text.c_str());

        setlinecolor(BLACK);
        if (isSelected && showCursor)
        {
            int cursorX = x + 5 + textwidth(text.substr(0, cursorPos).c_str());
            line(cursorX, y + 2 + height / 8, cursorX, y + height * 7 / 8 - 2);
        }
    }

    bool checkClick(int mouseX, int mouseY)
    {
        if (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height)
        {
            isSelected = true;
            return true;
        }
        else
        {
            isSelected = false;
            cursorPos = text.length();
            return false;
        }
    }

    void keyInput(wchar_t ch)
    {
        if (isSelected)
        {
            switch (ch)
            {
                case '\b':				// 用户按退格键，删掉一个字符
                    if (!text.empty() && cursorPos > 0)
                    {
                        text.erase(cursorPos - 1, 1);
                        cursorPos--;
                    }
                    break;
                case '\r':
                case '\n':
                    cursorPos = text.length();
                    isSelected = false;
                    break;
                default:				// 用户按其它键，接受文本输入
                    if (text.length() < maxWord)
                    {
                        text.insert(cursorPos, 1, ch);
                        cursorPos++;
                    }
            }
        }
    }

    void updateCursor()
    {
        static DWORD lastTick = GetTickCount();
        DWORD currentTick = GetTickCount();
        if (currentTick - lastTick >= 500) // 每500毫秒切换光标状态
        {
            showCursor = !showCursor;
            lastTick = currentTick;
        }
    }
};

class Widget
{
private:
    int width;
    int height;
    int currentIndex;
    vector<IMAGE*> pages;
    vector<vector<Button*>> buttons;
    vector<vector<TextBox*>>textBoxs;

    void addPage(IMAGE* page)
    {
        pages.push_back(page);
        buttons.push_back({});
        textBoxs.push_back({});
    }

    void addButton(int index, Button* button)
    {
        if (index >= 0 && index < buttons.size())
        {
            buttons[index].push_back(button);
        }
    }

    void addTextBox(int index, TextBox* textBox)
    {
        if (index >= 0 && index < textBoxs.size())
        {
            textBoxs[index].push_back(textBox);
        }
    }

    void setCurrentIndex(int index)
    {
        if (index >= 0 && index < pages.size())
        {
            currentIndex = index;
        }
    }

    void mouseClick(int mouseX, int mouseY)
    {
        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                if (button->checkClick(mouseX, mouseY))
                {
                    break;
                }
            }
        }
        if (currentIndex >= 0 && currentIndex < textBoxs.size())
        {
            for (auto textbox: textBoxs[currentIndex])
            {
                textbox->checkClick(mouseX, mouseY);
            }
        }
    }

    void mouseMove(int mouseX, int mouseY)
    {

        if (currentIndex >= 0 && currentIndex < buttons.size())
        {
            for (Button* button : buttons[currentIndex])
            {
                button->checkMouseOver(mouseX, mouseY);
            }
        }
    }

    void keyInput(wchar_t ch)
    {
        if (currentIndex >= 0 && currentIndex < textBoxs.size())
        {
            for (auto textbox:textBoxs[currentIndex])
            {
                if (textbox->getSelect())
                {
                    textbox->keyInput(ch);
                }
            }
        }
    }

    void draw()
    {
        if (currentIndex >= 0 && currentIndex < pages.size())
        {
            putimage(0, 0, pages[currentIndex]);

            if (currentIndex >= 0 && currentIndex < buttons.size())
            {
                for (Button* button : buttons[currentIndex])
                {
                    button->draw();
                }
            }

            if (currentIndex >= 0 && currentIndex < textBoxs.size())
            {
                for (auto textbox: textBoxs[currentIndex])
                {
                    if (textbox->getSelect())
                    {
                        textbox->updateCursor();
                    }
                    textbox->draw();
                }
            }
        }
    }

public:
    Widget(int width, int height)
            :width(width), height(height), currentIndex(-1)
    {
    }
    ~Widget() {}

    void init()
    {
        initgraph(width, height);

        // 创建页面1
/*        IMAGE* page1 = new IMAGE(width, height);
        setfillcolor(RGB(240, 240, 240));
        solidrectangle(0, 0, width, height);
        getimage(page1, 0, 0, width, height);
        setcurrentindex(0);切换界面
        addPage(page1);*/
        IMAGE* page1 = new IMAGE;
        loadimage(page1, "C:/Users/Administrator/Desktop/OIP-C.png",width,height);

        addPage(page1);

        // 在界面1创建按钮1
        Button* button1_1 = new Button(300, 400, 150, 30, "single player", [&]() {
                                           //转到单人游戏
                                       }
        );
        addButton(0, button1_1);

        Button* button1_2 = new Button(300, 450, 150, 30, "multi player", [&]() {
                                           setCurrentIndex(1);
                                       }
        );
        addButton(0, button1_2);

        // 创建页面2
        IMAGE* page2 = new IMAGE;
        loadimage(page2, "C:/Users/Administrator/Desktop/OIP-C.png",width,height);

        addPage(page2);

        TextBox* textbox1 = new TextBox(200, 300, 300, 30, 10);
        addTextBox(1, textbox1);


        TextBox* textbox2 = new TextBox(200, 350, 300, 30, 10);
        addTextBox(1, textbox2);


        // 在界面2创建按钮1
        Button* button2_1 = new Button(200, 400, 100, 30, "back", [&]() {
            setCurrentIndex(0);
        });
        addButton(1, button2_1);

        Button* button2_2 = new Button(400, 400, 100, 30, "confirm", [&]() {
                                           //转到多人游戏
                                       }
        );
        addButton(1, button2_2);

        setCurrentIndex(0);
    }

    void run()
    {
        ExMessage msg;

        BeginBatchDraw();
        while (true)
        {
            if (peekmessage(&msg))
            {
                int mouseX = msg.x;
                int mouseY = msg.y;
                switch (msg.message)
                {
                    case WM_LBUTTONDOWN:
                        mouseClick(mouseX, mouseY);
                        break;
                    case WM_MOUSEMOVE:
                        mouseMove(mouseX, mouseY);
                        break;
                    case WM_CHAR:
                        keyInput(msg.ch);
                        break;
                }
            }
            draw();
            FlushBatchDraw();
            Sleep(10);
        }
        EndBatchDraw();
    }

    void close()
    {
        closegraph();
    }
};

int main()
{
    Widget widget(800, 600);
    widget.init();
    widget.run();
    widget.close();
    return 0;
}