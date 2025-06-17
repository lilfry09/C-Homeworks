from flask import Flask, render_template, request, jsonify
import requests
import json
import os

app = Flask(__name__)

# API配置
api_key = "sk-CE3D31CD448C43B8BE7F0BF798817492"
base_url = "http://10.119.11.146:3000/v1"

# 设置请求头
headers = {
    "Content-Type": "application/json",
    "Authorization": f"Bearer {api_key}"
}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api/chat', methods=['POST'])
def chat():
    data = request.json
    messages = data.get('messages', [])
    model = data.get('model', 'gpt-3.5-turbo')
    
    try:
        # 添加重试机制
        max_retries = 3
        retry_count = 0
        
        while retry_count < max_retries:
            try:
                response = requests.post(
                    f"{base_url}/chat/completions",
                    headers=headers,
                    json={
                        "model": model,
                        "messages": messages,
                        "temperature": 0.7
                    },
                    timeout=30
                )
                
                if response.status_code == 200:
                    return jsonify(response.json())
                elif response.status_code == 503:
                    # 服务不可用，尝试重试
                    retry_count += 1
                    if retry_count < max_retries:
                        # 等待一段时间再重试
                        import time
                        time.sleep(2)  # 等待2秒
                        continue
                    else:
                        return jsonify({
                            "error": "服务暂时不可用，请稍后再试",
                            "details": f"API返回503错误: {response.text}"
                        }), 503
                else:
                    return jsonify({
                        "error": f"API返回错误: {response.status_code}",
                        "details": response.text
                    }), response.status_code
            except requests.exceptions.Timeout:
                retry_count += 1
                if retry_count < max_retries:
                    import time
                    time.sleep(2)  # 等待2秒
                    continue
                else:
                    return jsonify({"error": "请求超时，请稍后再试"}), 504
            except requests.exceptions.ConnectionError:
                return jsonify({"error": "无法连接到API服务器，请检查网络连接或服务器状态"}), 502
    except Exception as e:
        return jsonify({"error": f"请求错误: {str(e)}"}), 500

@app.route('/api/models', methods=['GET'])
def get_models():
    try:
        # 添加重试机制
        max_retries = 3
        retry_count = 0
        
        while retry_count < max_retries:
            try:
                response = requests.get(f"{base_url}/models", headers=headers, timeout=10)
                
                if response.status_code == 200:
                    return jsonify(response.json())
                elif response.status_code == 503:
                    # 服务不可用，尝试重试
                    retry_count += 1
                    if retry_count < max_retries:
                        # 等待一段时间再重试
                        import time
                        time.sleep(2)  # 等待2秒
                        continue
                    else:
                        return jsonify({
                            "error": "获取模型失败: 服务暂时不可用，请稍后再试",
                            "details": f"API返回503错误"
                        }), 503
                else:
                    return jsonify({"error": f"获取模型失败: {response.status_code}"}), response.status_code
            except requests.exceptions.Timeout:
                retry_count += 1
                if retry_count < max_retries:
                    import time
                    time.sleep(2)  # 等待2秒
                    continue
                else:
                    return jsonify({"error": "请求超时，请稍后再试"}), 504
            except requests.exceptions.ConnectionError:
                return jsonify({"error": "无法连接到API服务器，请检查网络连接或服务器状态"}), 502
    except Exception as e:
        return jsonify({"error": f"请求错误: {str(e)}"}), 500

# 只有在直接运行此脚本时才会执行
# 在PythonAnywhere上通过WSGI运行时不会执行这部分代码
if __name__ == '__main__':
    print("✅ 网页聊天应用已创建！")
    print("🚀 运行以下命令启动应用：")
    print("   flask run --host=0.0.0.0 --port=5000")
    print("   然后在浏览器中访问: http://localhost:5000")
    
    # 尝试使用不同的端口
    try:
        app.run(host='0.0.0.0', port=5000, debug=True)
    except OSError:
        print("端口5000被占用，尝试使用端口5001...")
        app.run(host='0.0.0.0', port=5001, debug=True)
