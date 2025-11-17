import psycopg2
import requests

def check_connection():
    try:
        connection = psycopg2.connect(
            host="localhost",
            database="postgres",
            user="postgres",
            password="Gerfederer44",
            port="5432"
        )
        cursor = connection.cursor()
        cursor.execute('SELECT 1')
        return True
    except psycopg2.Error as e:
        print(f"Error connecting to database: {e}")
        return False
    
print(check_connection())
