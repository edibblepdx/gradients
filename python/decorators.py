def exception_handler(func):
    def wrapper(*args, **kwargs):
        try:
            return func(*args, **kwargs)
        except (TypeError, ValueError):
            print(f"{func.__name__}: invalid argument(s)")
            return None
    return wrapper 