
#include "calendar.h"
#include "sort.h"
#include "dateutils.h"
#include <assert.h>

// Globale Variable sortierung ist dafür da,
// damit listCalendar() weiß, wonach es die Ausgabe gruppieren soll.
// Default ist Sort_None - Keine Sortierung ausgewählt.
Sortierung sortierung = Sort_None;

/**********************************************************/
/* Aus dem Skript geklaut und angepasst                   */
/* int partitionCalendar(int ui, int oi)                  */
/* Unterteilt das Calendar-Array in zwei Teile, wobei     */
/* im linken Teil alle Werte kleiner und im rechten Teil  */
/* alle Werte größer als die mittlere Schranke sind. Der  */
/* Index der Schranke wird zurückgegeben.                 */
/* Parameter: ui    - der untere Index des Teils des      */
/*                    Arrays, der sortiert werden soll    */
/*            oi    - der obere Index (entsprechend ui)   */
/* Rückgabe:  int   - Index der Schranke                  */
/**********************************************************/
static int partitionCalendar(short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*), int ui, int oi)
{
   int i = ui, j = oi;   /* Laufindizes */
   TAppointment *comp = Calendar + ui; /* Vergleichselement (Schranke) */

   while (i <= j)
   {
      /* nächstes Element > comp von links suchen (im linken Teil) */
      while (i <= j && compare(Calendar + i, comp) <= 0)
         i++;

      /* nächstes Element < comp von rechts suchen (im rechten Teil) */
      while (j >= i && compare(Calendar + j, comp) >= 0)
         j--;

      if (i < j)
      {
         swapApps(Calendar + i, Calendar + j);
         i++;
         j--;
      }
   }

   i--;

   /* setze Vergleichselement (Schranke) zwischen beide Teile */
   swapApps(Calendar + ui, Calendar + i);

   return(i);
}

/**********************************************************/
/* void qsortCalendar(, int ui, int oi)                   */
/* Unterteilt das Calendar-Array in zwei Teile (Funktion  */
/* partition) und ruft sich selber für beide Teile        */
/* erneut auf.                                            */
/* Parameter: ui    - der untere Index des Teils des      */
/*                    Arrays, der sortiert werden soll    */
/*            oi    - der obere Index (entsprechend ui)   */
/* Rückgabe:  keine                                       */
/**********************************************************/
static void qsortCalendar(short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*), int ui, int oi)
{
   int idx;   /* Schranke einer Zerlegung */

   if (ui >= oi)
      return;
   else
   {
      idx = partitionCalendar(compare, swapApps, ui, oi);
      qsortCalendar(compare, swapApps, ui, idx - 1); /* linken Teil rekursiv sortieren */
      qsortCalendar(compare, swapApps, idx + 1, oi); /* rechten Teil rekursiv sortieren */
   }
}

/***********************************************************/
/* Quick-Sort aus dem Skript geklaut und angepasst.        */
/* Sortiert das angegebene Zahlen-Array in aufsteigender   */
/* Reihenfolge.                                            */
/* Parameter: Array  - Zeiger auf das zu sortierende Array */
/*            Anzahl - Anzahl der Elemente im Array        */
/* Rückgabe:  keine                                        */
/***********************************************************/
static void _quickSortCalendar(short (*compare)(TAppointment const*, TAppointment const*), void (*swapApps)(TAppointment*, TAppointment*))
{
    qsortCalendar(compare, swapApps, 0, AppointmentCount - 1);

    // Globale sortierungs-Variable setzen, damit listCalendar() weiß, wonach sortiert ist.
    if (compare == cmpApps_DateTime)
        sortierung = Sort_DateTime;
    else if (compare == cmpApps_DescDateTime)
        sortierung = Sort_DescDateTime;
    else if (compare == cmpApps_DurDateTime)
        sortierung = Sort_DurDateTime;
    else if (compare == cmpApps_LocDateTime)
        sortierung = Sort_LocDateTime;
    else
        assert(0);
}

// Es gibt als Swap-Funktion nur eine einzige, diese wird hier eingesetzt.
void quickSortCalendar(short (*compare)(TAppointment const*, TAppointment const*))
{
    _quickSortCalendar(compare, swapAppointments);
}
