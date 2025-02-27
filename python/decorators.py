import time

def exception_handler(func):
    def wrapper(*args, **kwargs):
        try:
            return func(*args, **kwargs)
        except (TypeError, ValueError):
            print(f"{func.__name__}: invalid argument(s)")
            return None
    return wrapper 

def timer(func):
    def wrapper(*args, **kwargs):
        t = time.time()
        res = func(*args, **kwargs)
        print(f"{func.__name__} took {t - time.time()}")
        return res
    return wrapper
