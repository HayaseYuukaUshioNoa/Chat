import smtplib

from email.mime.text import MIMEText


def send_mail(uname: str, pwd: str, verifycode: str) -> bool:
    try:
        # smtp服务器
        smtp_server = "smtp.qq.com"
        # smtp端口
        smtp_port = 465
        # 发送者
        sender = uname
        # 授权码
        password = pwd
        # 接收者
        receiver = "1846349950@qq.com"

        content = f"验证码: {verifycode}"
        message = MIMEText(content, "plain", "utf-8")
        message["From"] = sender
        message["To"] = receiver
        message["Subject"] = "验证码"

        # SSL连接
        server = smtplib.SMTP_SSL(smtp_server, smtp_port)
        # 打印调试信息
        server.set_debuglevel(1)
        # 登录邮箱
        server.login(sender, password)
        # 发送邮件
        server.sendmail(sender, receiver, message.as_string())
        print(f"send mail success")
        return True
    except Exception as e:
        print(f"send mail failed: {e}")
        return False
