from pathlib import Path
import sys
import pandas as pd
import matplotlib.pyplot as plt

# Użycie:
# python srednie_wykresy_csv.py
# albo:
# python srednie_wykresy_csv.py "C:\\sciezka\\do\\folderu\\z\\csv"

def wczytaj_csv(sciezka: Path) -> pd.DataFrame:
    return pd.read_csv(
        sciezka,
        sep=';',
        header=None,
        names=['seria', 'n', 'czas_ns'],
        encoding='utf-8'
    )

def policz_srednia_po_seriach(df: pd.DataFrame) -> pd.DataFrame:
    # Dla każdego n liczymy średni czas ze wszystkich serii
    srednie = (
        df.groupby('n', as_index=False)['czas_ns']
        .mean()
        .sort_values('n')
    )
    return srednie

def rysuj_plik(csv_path: Path, output_dir: Path) -> None:
    df = wczytaj_csv(csv_path)
    srednie = policz_srednia_po_seriach(df)

    plt.figure(figsize=(12, 7))
    plt.plot(
        srednie['n'],
        srednie['czas_ns'],
        marker='o',
        linestyle='-',
        linewidth=1.5,
        markersize=3
    )

    plt.title(f'{csv_path.stem} - średnia z serii')
    plt.xlabel('n')
    plt.ylabel('średni czas [ns]')
    plt.grid(True, alpha=0.3)
    plt.tight_layout()

    out_file = output_dir / f'{csv_path.stem}_srednia.png'
    plt.savefig(out_file, dpi=150)
    plt.close()
    print(f'Zapisano: {out_file}')

def zapisz_tabele_srednich(csv_path: Path, output_dir: Path) -> None:
    df = wczytaj_csv(csv_path)
    srednie = policz_srednia_po_seriach(df)
    out_csv = output_dir / f'{csv_path.stem}_srednia.csv'
    srednie.to_csv(out_csv, index=False)
    print(f'Zapisano: {out_csv}')

def main():
    if len(sys.argv) > 1:
        folder = Path(sys.argv[1]).expanduser().resolve()
    else:
        folder = Path(__file__).resolve().parent

    if not folder.exists():
        print(f'Nie istnieje folder: {folder}')
        return

    pliki = sorted(folder.glob('S2_*.csv'))

    if not pliki:
        print(f'Nie znaleziono plików S2_*.csv w katalogu: {folder}')
        return

    output_dir = folder / 'wykresy_srednie'
    output_dir.mkdir(exist_ok=True)

    for csv_path in pliki:
        try:
            zapisz_tabele_srednich(csv_path, output_dir)
            rysuj_plik(csv_path, output_dir)
        except Exception as e:
            print(f'Błąd dla {csv_path.name}: {e}')

    print(f'\nGotowe. Wyniki są w folderze: {output_dir}')

if __name__ == '__main__':
    main()