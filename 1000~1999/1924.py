from datetime import date

def main():
    month, day = map(int, input().split())
    curDate = date(2007, month, day)

    print(curDate.strftime("%a").upper())

if __name__ == "__main__":
    main()