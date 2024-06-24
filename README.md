numarare: complexitate: (O(N + M))

Incepem prin a citi cele doua grafuri cu ajutorul functiei read_graph care citeste M muchii orietate,stocate sub forma unor liste de adiacenta. Mai apoi se folosește funcția intersect_graphs pentru a construi un nou graf care conține doar muchiile care sunt prezente în ambele grafuri inițiale.

### intersect_graphs

Această funcție primește ca argumente două liste de adiacență, g1 și g2, care reprezintă cele două grafuri DAG. Funcția returnează o nouă listă de adiacență care conține doar muchiile care aparțin ambelor grafuri.

1. Se creează un vector de vectori (listă de adiacență) common pe baza numărului maxim de noduri dintre cele două grafuri pentru a asigura că poate conține toate nodurile posibile.

2. Se parcurge fiecare nod i până la numărul maxim de noduri dintre cele două grafuri. Pentru fiecare nod, se verifică muchiile asociate în ambele grafuri.

3. Pentru nodul curent i, se adaugă într-un set common_edges toate nodurile vecine din g1[i]. Acest set ajută la verificarea rapidă dacă o anumită muchie există în ambele grafuri.

4. Se parcurg vecinii nodului i din al doilea graf g2. Dacă un vecin (să zicem edge) este găsit și în setul common_edges (adică există și în g1), atunci aceasta este o muchie comună și se adaugă în lista de adiacență a grafului comun la nodul i.

Funcția count_common_paths calculează numărul de căi de la nodul start la nodul de destinație, folosind programare dinamică.

### count_common_paths

1. Se creaza un vector dp[] pentru a retine numarul de cai de la de la nodul de start la nodul index si un vector in_degree care retine gradul intern al fiecarui nod index.

2. Iterăm prin nodurile și muchiile lor pentru a incrementa gradul nodurilor destinație.

3. Se folosește un queue pentru a gestiona nodurile care trebuie procesate. Nodurile cu grad de intrare 0 sunt adăugate inițial în coadă, semnificând că pot fi procesate independent. Vectorul dp este utilizat pentru a stoca numărul de căi de la nodul start la fiecare nod i. Când un nod j este procesat, acesta adaugă întoarcerea valorii sale dp nodurilor către care pointează. Oricând un nod este prelucrat (adică scoatem din coadă), decrementăm gradul de intrare pentru nodurile vecine și, dacă gradul devine 0, adăugăm nodul în coadă pentru procesare ulterioară.

4. Numarul final de cai comune este dp[N-1].



trenuri: complexitate: O(N + M)

Programul folosește o abordare de tipul sortării topologice combinate cu dinamica pe grafuri pentru a determina cea mai lungă cale într-un graf orientat aciclic.Utilizează unordered_map pentru a indexa orașele și o listă de adiacență pentru a reprezenta structura grafului.Odată ce toate orașele au fost indexate și graful este construit, este realizată o sortare topologică pentru a garanta procesarea nodurilor în ordinea corectă pentru a calcula cea mai lungă cale posibilă de la orașul de start la orașul de destinație.

### topologicalSort()

Funcția completează o parcurgere în adâncime (DFS) pornind de la nodul specificat v și vizitează toate nodurile la care se poate ajunge din v și care nu au fost vizitate anterior.

Parametri:
- v: Nodul curent care este procesat.
- adj: Lista de adiacență a grafului care reprezintă muchiile între noduri.
- visited: Un vector care ține evidența nodurilor vizitate pentru a evita procesarea repetată a acelorași noduri.
- stack: O stivă utilizată pentru a păstra ordinea nodurilor în sortarea topologică.

1. Marchează nodul v ca vizitat.
2. Pentru fiecare nod vecin i care nu a fost vizitat, apelează recursiv topologicalSort().
3. După ce toate nodurile accesibile din v sunt vizitate, adaugă v în stivă. Acest pas asigură că toate nodurile care depind de v sunt deja în stivă înainte de v (principiul sortării topologice).

### maxPathCities()

Această funcție calculează cel mai lung drum de la orașul de start la orașul de destinație folosind rezultatele sortării topologice.

Parametri:
- start: Orașul de plecare.
- end: Orașul de destinație.
- adj: Lista de adiacență a grafului.
- indices: Un map care asociază fiecare oraș cu un index unic.

1. Inițializează un vector de vizite și o stivă pentru a efectua sortarea topologică a tuturor nodurilor.
2. După finalizarea sortării topologice, inițializează un vector dist și setează distanța la orașul de start la 1 (toate celelalte sunt 0).
3. Cât timp stiva nu este goală:
- Scoate un nod u din stivă.
- Pentru fiecare nod vecin i, actualizează dist[i] dacă o nouă cale mai lungă este găsită prin u.
- Returnează valoarea din dist ușând idx-ul orașului de destinație.



drumuri: complexitate: O((N + M) log N),

Acest program este destinat să calculeze suma minimă a unei submulțimi de muchii astfel încât să existe un drum de la nodul x la nodul z și un drum de la nodul y la nodul z într-un graf orientat cu costuri pe muchii.

Programul folosește algoritmul lui Dijkstra pentru a determina costurile minime de la nodul z la toate celelalte noduri din graf. Rezultatul reprezintă suma costurilor drumurilor minime de la nodul x la z și de la nodul y la z.

### dijkstra()

Această funcție calculează distanțele minime de la un nod sursă dat la toate celelalte noduri dintr-un graf, folosind algoritmul lui Dijkstra.

Parametri:
- source: Nodul sursă de la care începe calculul distanțelor.
- adj: Lista de adiacență a grafului, unde fiecare nod este asociat cu un vector de perechi. Fiecare pereche reprezintă un nod conectat și costul de a ajunge la acest nod.
- n: Numărul de noduri din graf.

Proces:
- Inițializează un vector de distanțe cu infinit (INF) pentru toate nodurile, cu excepția sursei care este inițializată cu 0.
- Utilizează o coadă de prioritate pentru a extrage nodul curent cu cea mai mică distanță estimată.
- Pentru fiecare nod vecin, actualizează distanța dacă un cost de drum mai mic este găsit prin nodul curent.
- Returnează vectorul de distanțe.

### main()

Funcția main gestionează citirea datelor de intrare din fișier, apelurile funcției Dijkstra și scrierea rezultatului în fișierul de ieșire.

Proces:
- Citește numărul de noduri și muchii din fișier.
- Construiește lista de adiacență a grafului pe baza datelor de intrare.
- Citește nodurile x, y, z.
- Calculează costurile minime de la nodul z la toate nodurile folosind Dijkstra.
- Calculează suma drumurilor de la x la z și de la y la z și scrie rezultatul în fișierul de ieșire.




scadal: complexitate: O(N + M)

Programul folosește un algoritm bazat pe reprezentarea problemelor de satisfacție cu restricții printr-un graf orientat și detectarea componentelor tare conexe pentru a determina configurația validă a invitațiilor.

#### addImp(int a, int b)
Adaugă o implicație logică de formă A implică B în reprezentarea grafică, unde A și B sunt transformate în indici de noduri grafice.
Această funcție manipulează indicii nodurilor pentru a reflecta implicațiile și adaugă o muchie de la a la b în graf, reflectând implicația A -> B. Modificarea indiciilor ajută la distingerea între variabilele pozitive și negative (de exemplu, invitat / neinvitat).

#### aORb(int a, int b)
Procesează și adaugă condițiile de tipul “OR” între doi prieteni sub forma de implicații logice în graf.
Funcția transformă o regula de forma “A sau B” în implicații:
dacă A este fals, atunci B trebuie să fie adevărat si vice-versa

#### dfsF(int node)
Această funcție îndeplinește parcurge DFS pentru a popula stiva cu noduri într-o ordine specifică, pentru a face sortarea topologică pentru aflarea componentei tare conexe.

#### dfsB(int node)
Un alt DFS care, pornind de la nodurile stocate în stivă (pe baza sortării topologice), găsește componente tare conexe. ctc[node] indică indicele componentei tare conexe din care face parte nodul.

#### setCol(int act, int mCol)
Folosită pentru a atribui valori (culori / adevărat sau fals) nodurilor din aceeași componentă tare conexă. Asigură că toate nodurile din aceeași componentă tare conectată au aceeași valoare logică (invitat sau nu).

1. Transformare reguli în implicații: Prin addImp și aORb, regulile date sunt convertite într-un format utilizabil pentru construcție de graf și evaluare logică.
2. Detectarea componentelor tare conexe (SCC): Utilizează dfsF și dfsB.
3. Atribuirea valorilor: Odată ce componentele tare conexe sunt identificate, setCol este utilizată pentru stabilirea definitivă a statutului fiecărui invitat (dacă sunt incluși sau nu în lista definitivă).
