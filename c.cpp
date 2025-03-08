import sys
import requests
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton, QVBoxLayout
from PyQt5.QtCore import Qt

class WeatherApp(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Weather App")
        self.setGeometry(100, 100, 400, 200)

        vbox = QVBoxLayout()

        self.city_label = QLabel("Nhập vào thông tin thành phố:", self)
        vbox.addWidget(self.city_label)

        self.city_input = QLineEdit(self)
        vbox.addWidget(self.city_input)

        self.get_weather_button = QPushButton("Tìm thời tiết", self)
        self.get_weather_button.clicked.connect(self.check_weather)
        vbox.addWidget(self.get_weather_button)

        self.temperature_label = QLabel("Nhiệt độ:", self)
        vbox.addWidget(self.temperature_label)

        self.emoji_label = QLabel("☀️", self)
        vbox.addWidget(self.emoji_label)

        self.description_label = QLabel("Thời tiết:", self)
        vbox.addWidget(self.description_label)

        self.setLayout(vbox)

    def check_weather(self):
        city = self.city_input.text()
        if city:
            weather = self.get_weather(city)
            if weather:
                self.temperature_label.setText(f"Nhiệt độ: {weather['temp']}°C")
                self.emoji_label.setText(weather['emoji'])
                self.description_label.setText(f"Thời tiết: {weather['description']}")
            else:
                self.temperature_label.setText("Không thể lấy thông tin thời tiết. Vui lòng thử lại.")
                self.emoji_label.setText("")
                self.description_label.setText("")
        else:
            self.temperature_label.setText("Vui lòng nhập tên thành phố.")
            self.emoji_label.setText("")
            self.description_label.setText("")

    def get_weather(self, city):
        api_key = "YOUR_API_KEY"  
        base_url = "http://api.openweathermap.org/data/2.5/weather"
        params = {
            'q': city,
            'appid': api_key,
            'units': 'metric',
            'lang': 'vi'  # Sử dụng tiếng Việt
        }
        response = requests.get(base_url, params=params)
        if response.status_code == 200:
            data = response.json()
            weather = data['weather'][0]['description']
            temperature = data['main']['temp']
            if 'rain' in weather:
                emoji = '🌧️'
            elif 'clear' in weather:
                emoji = '☀️'
            elif 'cloud' in weather:
                emoji = '☁️'
            elif 'snow' in weather:
                emoji = '❄️'
            else:
                emoji = '🌡️'
            return {'description': weather, 'temp': temperature, 'emoji': emoji}
        else:
            return None

if __name__ == "__main__":
    app = QApplication(sys.argv)
    weather_app = WeatherApp()
    weather_app.show()
    sys.exit(app.exec_())
